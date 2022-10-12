instance ArticulatedObject pend
system pend load sdfast $env(DANCE_DIR)/sdfastObjs/pend/pend.sd
system pend load state  $env(DANCE_DIR)/run/pend/lean.state

instance PlaneGround ground
actuator ground set model 27424 805 400
actuator ground set geometry -6.0 -6.0 -3.4 -6.0 -6.0 2.4 6.0 -6.0 2.4 6.0 -6.0 -3.4 10 10

#actuator ground texture_file mrjpaintingt.ppm
#actuator ground texture_mode 1

instance FieldActuator grav
actuator grav apply  all
actuator grav set field 0 -9.8 0

#instance view quadview
#instance view front front 40 40 400 400
#instance view right right 460 40 400 400
instance view persp persp 100 100 640 480
instance light test
light test position 0.2 2.5 1 0
light test ambient 0.2 0.2 0.2 1.0
light test diffuse 0.5 0.5 0.5 1.0
light test specular 0.5 0.5 0.5 1.0
view persp lights on
view persp solids on
view persp shadows on
#view front lights on 
#view front solids on
#view front shadows on
#view perspective projection persp -1 1 -5 5 1 100 


instance IndexedFaceSet cube $env(DANCE_DIR)/data/models/cube.vrml
system pend link 0 geometry cube
system pend link 0 fit
system pend link 1 geometry cube
system pend link 1 fit

# actuator that can be used to record and playback data
instance KinematicActuator playBack
actuator playBack apply pend
# bring up the user inerface for the playBack mechanism
# Same thing can be done using Edit->Actuators->playBack
editKinematicActuator playBack KinematicActuator 

# instantiate a ParticlePointSystem plugin
instance ParticlePointSystem ps
# set some parameters for the particle point system
system ps birth_rate 200
system ps vel 0 -0.6 0.0
system ps life_time 2.0
system ps length 0.08
system ps source -0.5 0.5 -0.5 0.5 -0.6

# instantiate a simulator for the particle system 'ps'
instance ParticlePointSimul sps ps
simulator sps y_threshold -6.0
simulator sps fade_factor 0.5

# instantiate a simulator for the pendulum
# SdfastSimul is plugin wrapper for Sd/Fast generated models
# Check out Symbolic Dynamic Inc. for details.
instance SdfastSimul sim pend

# put everything in view
view persp fitview

# start the simulation
simul -setSimulationTimeStep 0.01
simul -setDisplayTimeStep 0.033
simul start






