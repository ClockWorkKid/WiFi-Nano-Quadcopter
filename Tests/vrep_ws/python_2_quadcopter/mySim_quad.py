# Code works with quadrirotor model
# scene_quadcopter.ttt
# simRemoteApi.start(19999)

import sim
import time
import sys


def init_sim_api():
    print('Program started')
    sim.simxFinish(-1)  # just in case, close all opened connections

    clientID = sim.simxStart('127.0.0.1', 19999, True, True, 5000, 5)  # Connect to CoppeliaSim

    return clientID


def init_quad(clientID):

    # Detatch the manipulation sphere:
    targetObj = sim.simxGetObjectHandle(clientID, 'Quadricopter_target', sim.simx_opmode_oneshot_wait)
    sim.simxSetObjectParent(clientID, targetObj, -1, True, sim.simx_opmode_oneshot)

    # Now try to retrieve data in a blocking fashion (i.e. a service call):
    res, objs = sim.simxGetObjects(clientID, sim.sim_handle_all, sim.simx_opmode_blocking)
    if res == sim.simx_return_ok:
        print('Number of objects in the scene: ', len(objs))
    else:
        print('Remote API function call returned with error code: ', res)

    _, motorLeft = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx_leftMotor', sim.simx_opmode_oneshot_wait)
    _, motorRight = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx_rightMotor', sim.simx_opmode_oneshot_wait)

    return motorLeft, motorRight


def close_sim_api(clientID):
    # Before closing the connection to CoppeliaSim, make sure that the last command sent out had time to arrive.
    # You can guarantee this with (for example):
    sim.simxGetPingTime(clientID)

    # Now close the connection to CoppeliaSim:
    sim.simxFinish(clientID)


def test_01():
    clientID = init_sim_api()

    if clientID == -1:
        print('Failed connecting to remote API server')
        sys.exit()

    else:
        print('Connected to remote API server')
        motorLeft, motorRight = init_quad(clientID)

        sim.simxSetJointTargetVelocity(clientID, jointHandle=motorLeft, targetVelocity=1,
                                       operationMode=sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, jointHandle=motorRight, targetVelocity=1,
                                       operationMode=sim.simx_opmode_oneshot)

        time.sleep(2)

        sim.simxSetJointTargetVelocity(clientID, jointHandle=motorLeft, targetVelocity=0,
                                       operationMode=sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, jointHandle=motorRight, targetVelocity=0,
                                       operationMode=sim.simx_opmode_oneshot)

        close_sim_api(clientID)
        print("closed simulation successfully")


if __name__ == "__main__":
    test_01()





