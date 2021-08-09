# led_tutorial

Provide LED control reference using Raspberry Pi and ROS

## basic_led_node

Provides a simple LED control example

### Diagram

![basic_led_diagram](./led_tutorial/diagram/basic_led.png)

### Run

```bash
roslaunch led_tutorial basic_led.launch
```

### Parameters

- ~LED_PIN (int, default: "0")

  Gpio Pin number corresponding to LED

----


## switch_on_led_node

Provides an example of LED control using a switch

### Diagram

![switch_on_led_diagram](./led_tutorial/diagram/switch_on_led.png)

### Run

```bash
roslaunch led_tutorial switch_on_led.launch
```

### Parameters

- ~LED_PIN (int, default: "0")

  Gpio Pin number corresponding to LED

- ~SwitchPin (int, default: "0")

  Gpio Pin number corresponding to Switch

