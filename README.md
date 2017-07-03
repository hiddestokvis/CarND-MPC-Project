# CarND-Controls-MPC
Self-Driving Car Engineer Nanodegree Program


## The Model

The vehicle model used for this project is the bicycle model. It's a relatively simple model where the 4 wheels of a car are simplified to a two wheel model as in a bicycle. It doesn't take things such as (wheel)friction, inertia and torque into account.

The model is decribed as followed:

![vehicle_model.png]

- ```x``` & ```y``` are the position of the car
- ```psi``` is the heading of the car
- ```v``` is the velocity
- ```cte``` is the cross-track error
- ```epsi``` is the orientation error
- ```Lf``` is the distance between the center of mass of the vehicle and the front wheels and it affects maneuverability.

## Timestep Length and Elapsed Duration (N * dt)

The timestep length and elapsed duration files where chosen empirically. I started off with the values ```N = 25``` and ```dt = 0.05``` as these where the values set in the MPC quiz. These values worked reasonably well but by testing I figured out I could decrease the N and therefor increase the performance (less calculations), with good results. At ```N = 10``` the car started to swivel around a little just before the corners, so it needed a little more information.  I found ```N = 12``` is the smallest value at which the car drives stable. Even at high speed (try increasing ```ref_v```).
In order to keep the latency in account the maximum ```dt``` can be ```.1``` the same as the latency. This way we can jump 1 step ahead to adjust for the latency. However we should aim for a smaller ```dt``` to increase accuracy. The next step would be ```dt = 0.05``` accounting for the latency by jumping two steps. One step lower at ```dt = 0.025``` resulted in the very poor performance as we would need much more steps here to get some real accuracy. I settled for the combination of ```N = 12``` and ```dt = 0.05```.

## Polynomial fitting and MPC Preprocessing

Before we can fit the polynomial we need to transfor the map coordinates to vehicle coordinates. Here we can use almost the same formulas as we applied in the Kidnapped vehicle project. The calculations are done in ```toCarCoordinates()``` function.

```
x_car = os(psi) * (ptsx[i] - x) + sin(psi) * (ptsy[i] - y);
y_car = -sin(psi) * (ptsx[i] - x) + cos(psi) * (ptsy[i] - y);
```

## MPC with latency

As the car executes the command with a 100ms delay the controller constantly needs to correct the trajectory which makes the car swivel over the road. I solved this by using the steer and throttle value of the predicted trajectory +100ms (or two steps of 0.05). This is a very easy way of making the car drive much more stable.
