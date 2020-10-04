# Code works with quadrirotor model
# scene_quad_multi.ttt
# simRemoteApi.start(19999)

import sim
import time
import sys
import numpy as np


class Simulation:

    def init(self):
        print('Starting Simulation')
        sim.simxFinish(-1)  # just in case, close all opened connections

        self.clientID = sim.simxStart('127.0.0.1', 19999, True, True, 5000, 5)  # Connect to CoppeliaSim

        return self.clientID

    def close(self):
        # Before closing the connection to CoppeliaSim, make sure that the last command sent out had time to arrive.
        # You can guarantee this with (for example):
        sim.simxGetPingTime(self.clientID)

        # Now close the connection to CoppeliaSim:
        sim.simxFinish(self.clientID)


class Quadcopter:

    def __init__(self, clientID):
        self.clientID = clientID
        self.quadHandle = None
        self.ID = ''
        self.targetHandle = None
        self.pos = np.zeros((1, 3))
        self.target_pos = np.zeros((1, 3))

    def init(self, ID = ''):
        self.ID = ID
        if ID == '':
            err, self.quadHandle = sim.simxGetObjectHandle(self.clientID, 'Quadricopter', sim.simx_opmode_blocking)
        else:
            err, self.quadHandle = sim.simxGetObjectHandle(self.clientID, 'Quadricopter#'+ID, sim.simx_opmode_blocking)
        if err != 0:
            print("Quadricopter " + ID + " Initialization failed")

        if ID == '':
            err, self.targetHandle = sim.simxGetObjectHandle(self.clientID, 'Quadricopter_target', sim.simx_opmode_blocking)
        else:
            err, self.targetHandle = sim.simxGetObjectHandle(self.clientID, 'Quadricopter_target#'+ID, sim.simx_opmode_blocking)
        if err != 0:
            print("Target " + ID + " Initialization failed")

        err, _ = sim.simxGetObjectPosition(self.clientID, self.targetHandle, -1, sim.simx_opmode_streaming)
        print('Initializing position for quadricopter ' + ID)
        err, self.target_pos = sim.simxGetObjectPosition(self.clientID, self.targetHandle, -1,
                                                             sim.simx_opmode_blocking)

    def get_pos(self):
        err, self.pos = sim.simxGetObjectPosition(self.clientID, self.quadHandle, -1, sim.simx_opmode_buffer)
        err = sim.simxSetObjectPosition(self.clientID, self.targetHandle, -1, self.target_pos, sim.simx_opmode_oneshot)
        if err != 0:
            print("Get Position " + self.ID + " failed")
        return self.pos

    def set_pos(self, target):
        self.target_pos = np.array(target)
        err = sim.simxSetObjectPosition(self.clientID, self.targetHandle, -1, self.target_pos, sim.simx_opmode_oneshot)
        if err != 0:
            print("Set target " + self.ID + " failed")

    def displacement(self, dist):
        self.target_pos = np.array(dist) + np.array(self.target_pos)
        err = sim.simxSetObjectPosition(self.clientID, self.targetHandle, -1, self.target_pos, sim.simx_opmode_oneshot)
        if err != 0:
            print("Set displacement " + self.ID + " failed")

def test_01():
    session = Simulation()
    clientID = session.init()

    quadID = ['', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14']
    quad = []

    if clientID == -1:
        print('Failed connecting to remote API server')
        sys.exit()

    else:
        print('Connected to remote API server')
        # initialize the quadcopter objects and connect to simulation handles
        for i in range(len(quadID)):
            quad.append(Quadcopter(clientID))
            quad[i].init(quadID[i])
        print("Quadcopters initialized")

        for i in range(5):

            for i in range(len(quadID)):
                quad[i].displacement(dist=[0.5, 0, 0])
            time.sleep(10)

            for i in range(len(quadID)):
                quad[i].displacement(dist=[0, 0.5, 0])
            time.sleep(10)

            for i in range(len(quadID)):
                quad[i].displacement(dist=[-0.5, 0, 0])
            time.sleep(10)

            for i in range(len(quadID)):
                quad[i].displacement(dist=[0, -0.5, 0])
            time.sleep(10)

        session.close()
        print("Simulation Terminated")


if __name__ == "__main__":
    test_01()





