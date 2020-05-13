# Black-box

Similar to how a black box is used in an airplane after a crash occurs to determine the reasons why it happened in the first place this is a black box which was specifically designed for cars.

The device tracks a cars features current features like the speed, its trajectory, carbon emission and the engine temperature and sends the data to Firebase for storage and viewing purposes.

## Components used
* ESP32
* MPU6050
* MQ135
* Firebase
* lm17

The carbon emissions of the car are regularly tracked and if they start to exceed a certain limit the **car owner is notified**. If the owner does not get it fixed within 15 days of the notification the **concerned authorities** so suitable action can be taken.

