# esp-fake-free-wifi
Be a menace and Create a fake free wifi Hotspot!
When People try to Log in with the Captive Portal, they get a not so nice suprise

## Demo
[Online Demo](https://larvenstein.github.io/esp-fake-free-wifi/login.html)

[!](https://user-images.githubusercontent.com/89642388/213938849-f9bd21c4-c301-486f-8dae-aa0e36ea7a9a.mp4)

## Installation 
1. Open your Arduino IDE and go to "File -> Preferences -> Additional Boards Manager URLs" and paste the following url: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
2. Go to "Tools -> Board -> Boards Manager", search "esp8266" and install esp8266
3. Select yor ESP8266 Board in "Tools -> Board"
4. Change the SSID, if yout want at `const char* SSID_NAME = "SSID HERE"`
5. Load `hotspot.ino` in your Arduino IDE and flash it to your ESP
