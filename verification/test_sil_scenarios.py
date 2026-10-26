import os
import pytest
import sys

sys.path.append(os.path.abspath("simulation/python"))

from bridge import SkyGuardBridge
from sim_engine import PlantSimulation

@pytest.fixture
def sim():
    lib_path = os.path.abspath("build/embedded/libskyguard.so")
    bridge = SkyGuardBridge(lib_path)
    return PlantSimulation(bridge)

def test_nominal_navigation(sim):
    """SYS-REQ-001: Ensure flight mode stays in NAV under normal operations"""
    for _ in range(100):
        mode = sim.run_step()
    assert mode == 1, "Flight mode should remain NAV (1) under nominal state"

def test_gps_loss_failsafe(sim):
    """SYS-REQ-003: GPS loss must trigger Return-To-Launch within 500ms"""
    for _ in range(50):
        sim.run_step()

    # Inject Fault: GPS Loss
    sim.gps_valid = False

    mode = sim.run_step()
    assert mode == 3, "Flight state machine failed to trigger RTL (3) on GPS failure"

def test_obstacle_avoidance(sim):
    """SYS-REQ-002: Obstacle within 2m must trigger AVOID mode"""
    sim.obstacle_dist = 1.5
    mode = sim.run_step()
    assert mode == 2, "Flight state machine failed to trigger AVOID (2) on proximity threat"
