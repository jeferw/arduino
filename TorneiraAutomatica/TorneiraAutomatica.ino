const int sensor_pin = A5;
const int led_pin_vermelho = 8;
const int led_pin_azul = 4;
const int led_pin_verde = 6;
const int rele_pin = 13;

const long tempo_max_aberta = 6000;

float media = 0.0;

int count;
int leitura = 0;
int _delay = 0;

boolean aberta = false;
boolean menor_valor = false;

unsigned long timeout;

void setup()
{
  delay(2000);

  pinMode(sensor_pin, INPUT);

  pinMode(led_pin_vermelho, OUTPUT);
  pinMode(led_pin_azul, OUTPUT);
  pinMode(led_pin_verde, OUTPUT);
  pinMode(rele_pin, OUTPUT);

  digitalWrite(led_pin_vermelho, LOW);
  digitalWrite(led_pin_azul, LOW);
  digitalWrite(led_pin_verde, LOW);
  digitalWrite(rele_pin, HIGH);
}

void loop()
{
  count = 0;
  leitura = 0;
  while (count <= 15)
  {
    leitura += (int)analogRead(sensor_pin);
    count++;

    delay(20);
  }

  media = (leitura / count);
  _delay = (int)(((1 / media) * 10000) * 2);

  if (media < 40)
  {
    desliga_torneira();
    menor_valor = true;
  } else if (media >= 40 && media < 65)
  {
    desliga_torneira();
    digitalWrite(led_pin_vermelho, HIGH);
    delay(_delay);
    digitalWrite(led_pin_vermelho, LOW);
    delay(_delay);
  } else if (media >= 65 && media < 90)
  {
    desliga_torneira();
    digitalWrite(led_pin_verde, HIGH);
    delay(_delay);
    digitalWrite(led_pin_verde, LOW);
    delay(_delay);
  } else if (media >= 90 && !aberta && menor_valor)
  {
    timeout = millis();
    aberta = true;
    digitalWrite(led_pin_azul, HIGH);
    digitalWrite(rele_pin, LOW);
    delay(2000);
  }

  if (aberta && (millis() - timeout >= tempo_max_aberta))
  {
    menor_valor = false;
    desliga_torneira();
  }
}

void desliga_torneira()
{
  if (aberta)
  {
    aberta = false;
    digitalWrite(led_pin_azul, LOW);
    digitalWrite(rele_pin, HIGH);
  }
}
