//                Red, Blue, Yellow, Green
const byte pins[] = {0, 1, 2, 3};
const byte tonePin = 4;
const int winMoves = 32; //amount of moves it takes to win (maximum of about 300, because of RAM)
const int initSpd = 500;

//const int tones[] = {  440,  330,  277,  165};
//const int tones[] = {  880,  659,  554,  330};
const int tones[] = { 1760, 1319, 1109,  659};
//const int tones[] = { 3520, 2637, 2217, 1319};
//const int tones[] = { 7040, 5274, 4435, 2637};
const int failTone = 400;


int spd = initSpd;
byte code[winMoves] = {0};
byte curMove = 0; //current code length
byte curStep = 0; //current user step inside code entry
byte btnState[4] = {1};

void setPinMode(int mode)
{
  for (int i = 0; i < 5; ++i)
    pinMode(pins[i], mode);
}

void setup() {
  randomSeed(analogRead(2));
  randomSeed(analogRead(2));
  randomSeed(analogRead(2));
  
  setPinMode(INPUT_PULLUP);
  for (int i = 0; i < 4; ++i)
    btnState[i] = digitalRead(pins[i]);
  pinMode(tonePin, OUTPUT);
  startGame();
}

void loop() {
  readBtns();
}

void lightAllBtns(bool state)
{
  for (int i = 0; i < 4; ++i)
  {
    pinMode(pins[i], state ? OUTPUT : INPUT_PULLUP);
    digitalWrite(pins[i], state ? LOW : HIGH);
  }
}

void lightBtn(byte btn, bool state)
{
  pinMode(pins[btn-1], state ? OUTPUT : INPUT_PULLUP);
  digitalWrite(pins[btn-1], state ? LOW : HIGH);
}


void playTone(byte pin)
{
  if (pin != 0)
    tone(tonePin, tones[pin-1]);
  else
    noTone();
}

void flashLeds()
{
  lightAllBtns(HIGH);
  delay(250);
  lightAllBtns(LOW);
  delay(250);
}

void readBtns()
{
  for (int i = 0; i < 4; ++i)
  {
    byte state = digitalRead(pins[i]);
    if (state != btnState[i])
    {
      btnState[i] = state;
      if (state)
      {
        playTone(0);
        procIn(i+1); //process on release
      }
      else
      {
        playTone(i+1);
      }
      break;
    }
  }
}


void showCode()
{
  for (int i = 0; i < curMove; ++i)
  {
    lightBtn(code[i], HIGH);
    playTone(code[i]);
    delay(spd);
    lightBtn(code[i], LOW);
    playTone(0);
    delay(spd);
  }
}


void genNextMove()
{
  curStep = 0;
  if (curMove % 5 == 0)
    spd = (spd * 4) / 5;
  if (curMove < winMoves)
  {
    code[curMove] = random(1,5); //Generate new digit
    curMove++;
    delay(1000);
    showCode();
  }
  else
    win();
}

void startGame()
{
  //todo: play tune
  flashLeds();
  genNextMove();
  delay(100);
}

void fail()
{
  //todo: fail tune
  tone(tonePin, failTone);
  flashLeds();
  flashLeds();
  noTone();
  reset();
  genNextMove();
}

void procIn(byte btn)
{
  if (btn == code[curStep])
  {
    curStep++;
    if (curStep == curMove)
      genNextMove();
  }
  else
    fail();
  delay(50); //debounce delay
}


void reset()
{
  for (int i = 0; i < winMoves; ++i)
  {
    code[i] = 0;
  }
  curMove = 0;
  spd = initSpd;
}

void win()
{
  //todo: play tune
  flashLeds();
  flashLeds();
  flashLeds();
  reset();
}

