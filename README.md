# Arduino Sprinkler Client

This project sets up an Arduino 3.3 IoT to act as a remote triggering client for a sprinkler system. The controller triggers off of 3.3V which must be regulated down from the 24VAC sprinkler system output (a full wave rectifier and a 200Ohm/20W resistor in parallel with a 3.3V buck converter will do). When triggered, this client sends a simple `HTTP GET /on` to a remote sprinkler receiver which then turns on a sprinkler valve. When the 24VAC goes to 0 the client sends an `HTTP GET /off` to the receiver to shut it off. 

Also see [the receiver code](https://github.com/alexbr/adafruit-sprinkler-receiver). 
