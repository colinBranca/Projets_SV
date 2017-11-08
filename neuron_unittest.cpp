#include "neuron.h"
#include "gtest/gtest.h"
namespace {


  TEST(neuron, updateState_1) {
    neuron* n = new neuron();
    n->setCurrent(0.9);
    for(int i = 0; i < 500; ++i) {
      n->updateState(i);
    }
    EXPECT_EQ(0, n->getSpikes());
  }

TEST(neuron, updateState_2) {
  neuron* n = new neuron();
  n->setCurrent(1.1);
  for(int i = 0; i < 500; ++i) {
    n->updateState(i);
  }
  EXPECT_EQ(1, n->getSpikes());
}

TEST(neuron, updateState_3) {
  neuron* n = new neuron();
  n->setCurrent(1);
  n->updateState(1);
  n->updateState(2);
  EXPECT_EQ(false, n->updateState(3));
}

TEST(neuron, updateState_4) {
  neuron* n = new neuron();
  n->setCurrent(1000);
  n->updateState(1);
  n->updateState(2);
  n->updateState(3);
  EXPECT_EQ(true, n->isRefractoring());
}

TEST(neuron, updateRefractoring) {
  neuron* n = new neuron();
  n->setCurrent(1000);
  for(int i=0; i < 22; ++i) {
    n -> updateState(i);
  }
  EXPECT_EQ(false, n->isRefractoring());
}

TEST(neuron, targets) {
  neuron* n = new neuron();
  std::vector<neuron*> targets;
  for(int i=0; i< 5; ++i) {
    neuron* ni = new neuron();
    n->addTarget(ni);
    targets.push_back(ni);
  }
  EXPECT_EQ(targets, n->getTargets());
}

TEST(neuron, receive) {
  neuron* n = new neuron();
  n->receive(0, 21);
  for(int i=0; i<16; ++i) {
    n->updateState(i);
  }
  EXPECT_EQ(true, n->updateState(16));
}

TEST(neuron, receiveFromExt) {
  neuron* n = new neuron();
  n->receiveFromExt(21);
  n->updateState(1);
  EXPECT_EQ(true, n->updateState(2));
}


}
