#include <Nextion.h>
#include <NextionPage.h>
#include <NextionVariableNumeric.h>
#include <NextionVariableString.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgVariable(nex, 10, 0, "pgVariable");
NextionVariableNumeric var1(nex, 10, 2, "vaExVariableN");
NextionVariableString var2(nex, 10, 3, "vaExVariableS");

/*
 * This example should print the following to the serial port:
 * 1
 * 4
 * Hello!
 */

void setup()
{
  Serial.begin(9600);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgVariable.show());

  var1.setValue(4);
  Serial.println(var1.getValue());

  var2.setText("Hello!");
  char buffer[20];
  if (var2.getText(buffer, 20))
    Serial.println(buffer);
}

void loop()
{
  nex.poll();
}
