
#include <ESP8266WiFi.h>
#include <DNSServer.h> 
#include <ESP8266WebServer.h>

// SSID
const char* SSID_NAME = "Free WiFi";



const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); 



unsigned long bootTime=0, lastActivity=0, lastTick=0, tickCtr=0;
DNSServer dnsServer; ESP8266WebServer webServer(80);

// Javascript
String JS {
  "function popup(){document.getElementById('popup').innerHTML='<a onclick=closepopup()>Schließen</a><h2>Nutzungsbedingungen</h2><p>Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Das ist nur ein Spaß. Hier gibt es kein Wlan. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.</p>',document.getElementById('popup').style.padding='15px'}function closepopup(){document.getElementById('popup').innerHTML='',document.getElementById('popup').style.padding='0'}function startmover(){if(1==document.getElementById('check').checked){let e,t;document.getElementById('btn').disabled=!1,e=Math.floor(500*Math.random())+-250+'px',t=Math.floor(500*Math.random())+-250+'px',document.getElementById('btn').style.transform='translate('+e+', '+t+')',function n(){setTimeout(function(){e=Math.floor(150*Math.random())+-75+'px',t=Math.floor(1100*Math.random())+-550+'%',document.getElementById('btn').style.transform='translate('+e+', '+t+')',1==document.getElementById('check').checked&&n()},245)}()}else document.getElementById('btn').disabled=!0}function clicked(){document.getElementById('replace').innerHTML='<header><h1 style=text-align:center>Tja<br>Wohl kein freis WLAN für dich :(</h1></header><main><h2 style=text-align:center>Dann musst du wohl doch einen Datentarif holen oder bei jemanden andres schnorren.<br>Viel Glück!</h2></main>'}"};


String header() {
  // CSS
  String CSS = "html { background: lightblue; width: 100vw; height: 100vh; overflow: hidden; }" 
    "body { font-family: Arial; position: absolute; top: 50%; left: 50%; transform: translate(-50%,-50%); background: white; border-radius: 15px; width: 90%; height: 90%; }"
    "main { display: grid; place-items: center;}"
    "header { display: grid; place-items: center; height: 33vh; width: 100%; background: lightgray; border-radius: 15px; }"
    "header div { text-align: center; transform: scale(2); }"
    "h1 { margin: 0; }"
    "input {transforn: scale(2);}"
    "label {font-size: xx-large;}"
    "#popup { position: absolute; top: 50%; left: 50%; transform: translate(-50%,-50%); background: lightblue; text-align: center; border-radius: 15px; }"        
    "a { text-decoration: underline; font-size: xx-large;}"
    "button { display: block; width: 100%; height: 45px; border-radius: 15px; transition: all .25s; font-size: xx-large;}"
    "button:enabled { background: lightblue; border: 0; }";    
    // Start of HTML
  String h = "<!DOCTYPE html><html>"
    "<head><title>Free Wifi Sign In</title>"
    "<meta charset=UTF-8>"
    "<style>" + CSS + "</style>"
    "<meta charset=\"UTF-8\"></head>"
    "<body id=replace>";
  return h; }

String index() {
// Bundle everything in HTML
  return header() + "<header><div><svg height=48 viewBox='0 0 24 24'width=48 xmlns=http://www.w3.org/2000/svg><path d='M4.504 13.572l-1.505-1.489c2.201-2.805 5.413-4.583 9.001-4.583s6.8 1.779 9 4.583l-1.504 1.489c-1.835-2.338-4.512-3.822-7.496-3.822s-5.661 1.484-7.496 3.822zm7.496.678c1.791 0 3.397.891 4.498 2.293l1.502-1.488c-1.467-1.869-3.608-3.055-6-3.055s-4.533 1.186-6 3.055l1.502 1.488c1.101-1.402 2.707-2.293 4.498-2.293zm0 2.25c-1.196 0-2.258.602-2.99 1.536l2.99 2.964 2.99-2.963c-.732-.935-1.794-1.537-2.99-1.537zm0-11.25c4.179 0 7.927 2.078 10.495 5.351l1.505-1.491c-2.935-3.739-7.217-6.11-12-6.11s-9.065 2.371-12 6.11l1.505 1.491c2.568-3.273 6.316-5.351 10.495-5.351z'/></svg><h1>Free Wifi</h1></div></header><main><form><h2 style=text-align:center>Login</h2><input id=check name=check onchange=startmover() type=checkbox> <label for=check>Ich akzeptiere die </label><a onclick=popup()>Nutzungsbedingungen</a><br><br><button disabled id=btn onclick=clicked()>EINLOGGEN</button></form></main><div id=popup></div><script>" + JS + "</script></body>";
}


void setup() {
  Serial.begin(115200);
  bootTime = lastActivity = millis();
  delay(10);


  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

  WiFi.softAP(SSID_NAME);  

  dnsServer.start(DNS_PORT, "*", APIP); 

  webServer.onNotFound([]() { lastActivity=millis(); webServer.send(HTTP_CODE, "text/html", index()); });
  webServer.begin();

}


void loop() { 
  if ((millis() - lastTick) > TICK_TIMER) {lastTick = millis();} 
dnsServer.processNextRequest(); webServer.handleClient(); }
