class Worker {
  float internalState;
  
  void processInput(float a) {
    internalState = a * 2;
  }
  
  float getState() {
    return internalState;
  }
}

Worker worker;

void setup() {
  size(480, 120);
  worker = new Worker();
}

void draw() {
  worker.processInput(mouseX);
  float x = worker.getState();
  ellipse(x, mouseY, 4, 4);
}
