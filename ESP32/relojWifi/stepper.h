//rojo: centro común
//bobina1: rosa + naranja
//bobina2: amarillo + azul


#define maxPasos 4095
#define numeroPins 4
#define numeroFases 8

int pins [numeroPins] = {12, 14, 27, 26};

int fases [numeroFases][numeroPins] = {{1,0,0,0},{1,1,0,0},
                                       {0,1,0,0},{0,1,1,0},
                                       {0,0,1,0},{0,0,1,1},
                                       {0,0,0,1},{1,0,0,1}};

int pasoActual = 0;
int faseActual = 0;


void stepperInit()
{
  for (int i = 0; i < numeroPins; i++)
  { pinMode(pins[i], OUTPUT); }
}


void stepperStep()
{
  faseActual += 1;
  if (faseActual == numeroFases) 
  { faseActual = 0; }
  for (int i = 0; i < numeroPins; i++)
  { digitalWrite(pins[i], fases[faseActual][i]); }
  pasoActual++;
  if (pasoActual == maxPasos)
  { pasoActual = 0; }
}
