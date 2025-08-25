// Arduino UNO Morse Blink
// Mors alfabesinde LED yanıp sönerek mesajı verir

const int ledPin = 13;

// Zaman birimleri (ms)
const int dotTime = 200;      // Nokta
const int dashTime = dotTime * 3; // Çizgi
const int symbolSpace = dotTime;  // Harf içi boşluk
const int letterSpace = dotTime * 3;
const int wordSpace = dotTime * 7;

// Morse kod tablosu
struct MorseSymbol {
  char letter;
  const char* code;
};

MorseSymbol morseTable[] = {
  {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
  {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
  {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
  {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
  {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
  {'Z', "--.."},
  {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
  {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
  {'8', "---.."}, {'9', "----."}
};

const int morseTableSize = sizeof(morseTable) / sizeof(morseTable[0]);

// Çıkış mesajı
const char* message = "ANNEMI COK SEVIYORUM";

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sendMessage(message);
  delay(10000); // mesaj arası uzun bekleme
}

void sendMessage(const char* msg) {
  for (int i = 0; msg[i] != '\0'; i++) {
    char c = toupper(msg[i]);

    if (c == ' ') {
      delay(wordSpace);
      continue;
    }

    const char* morse = findMorse(c);
    if (morse) {
      sendMorse(morse);
      delay(letterSpace);
    }
  }
}

const char* findMorse(char c) {
  for (int i = 0; i < morseTableSize; i++) {
    if (morseTable[i].letter == c) {
      return morseTable[i].code;
    }
  }
  return nullptr;
}

void sendMorse(const char* code) {
  for (int i = 0; code[i] != '\0'; i++) {
    if (code[i] == '.') {
      blink(dotTime);
    } else if (code[i] == '-') {
      blink(dashTime);
    }
    delay(symbolSpace);
  }
}

void blink(int duration) {
  digitalWrite(ledPin, HIGH);
  delay(duration);
  digitalWrite(ledPin, LOW);
  delay(symbolSpace);
}
