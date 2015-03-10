#include <iostream>
#include <yarp/os/all.h>

using namespace yarp::os;

int main(int argc, char *argv[]) {
  Network yarp;

  BufferedPort<Bottle> receiverBuff1;
  bool receiver1Ok = receiverBuff1.open("/generatedCode/receiver1");
  BufferedPort<Bottle> receiverBuff2;
  bool receiver2Ok = receiverBuff2.open("/generatedCode/receiver2");
  BufferedPort<Bottle> receiverBuff3;
  bool receiver3Ok = receiverBuff3.open("/generatedCode/receiver3");
  BufferedPort<Bottle> receiverBuff4;
  bool receiver4Ok = receiverBuff4.open("/generatedCode/receiver4");

  Port outputPort;
  outputPort.setWriteOnly();
  bool outputOk = outputPort.open("/vizzy/joint_states@/yarp/generatedCode");

  yarp.connect("/vizzySim/head/state:o", receiverBuff1.getName());
  yarp.connect("/vizzySim/torso/state:o", receiverBuff2.getName());
  yarp.connect("/vizzySim/left_shoulder_arm/state:o", receiverBuff3.getName());
  yarp.connect("/vizzySim/right_shoulder_arm/state:o", receiverBuff4.getName());

  std::cout << "Waiting for output..." << std::endl;
  while(outputPort.getOutputCount() == 0) {
    Time::delay(1);
    std::cout << ".\n";
  }
  std::cout << "Connection successfuly established." << std::endl;

  while(true){
    Bottle* reading1 = receiverBuff1.read();
    Bottle* reading2 = receiverBuff2.read();
    Bottle* reading3 = receiverBuff3.read();
    Bottle* reading4 = receiverBuff4.read();

    Bottle mutex;

    for(int i = 0; i < reading1->size(); i++) {
      mutex.add(reading1->get(i));
    }
    for(int i = 0; i < reading2->size(); i++) {
      mutex.add(reading2->get(i));
    }
    for(int i = 0; i < reading3->size(); i++) {
      mutex.add(reading3->get(i));
    }
    for(int i = 0; i < reading4->size(); i++) {
      mutex.add(reading4->get(i));
    }

    for(int i = 0; i < mutex.size(); i++) {
      mutex.get(i) = mutex.get(i).asDouble() / (180/3.1415926);
      std::cout << mutex.get(i).asDouble() << std::endl;
    }

    Bottle bottleToSend = Bottle();
    Bottle& header = bottleToSend.addList();
    header.addInt(3);
    Bottle& timeList = header.addList();
    header.addString("exp");
    Bottle& name = bottleToSend.addList();
    Bottle& pos = bottleToSend.addList();
    Bottle& vel = bottleToSend.addList();
    Bottle& eff = bottleToSend.addList();

    /*for(int i = 0; i < mutex.size(); i++) {
      listOnBottle.add(mutex.get(i));
    }*/

      timeList.addInt(12);
      timeList.addInt(12);
      name.addString("hey1");
      name.addString("hey2");
      pos.addDouble(0.5);
      pos.addDouble(0.5);
      vel.addDouble(0.5);
      vel.addDouble(0.5);
      eff.addDouble(0.5);
      eff.addDouble(0.5);

    outputPort.write(bottleToSend);

  }

  return 0;
}