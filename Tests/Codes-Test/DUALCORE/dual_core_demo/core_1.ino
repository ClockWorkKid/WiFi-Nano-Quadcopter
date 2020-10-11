#define N_1 16

int A_1[N_1][N_1], B_1[N_1][N_1], C_1[N_1][N_1];
unsigned long t1 = 0;
long int sum1;

void setup_1(){
  Serial.println("Core 1 initializing");
}

void loop_1(){
  
  for (int r = 0; r < N_1; r++){
    for (int c = 0; c < N_1; c++){
      A_1[r][c] = random(0, 100);
      B_1[r][c] = random(0, 100);
    }
  }

  t1 = micros();

  for (int r = 0; r < N_1; r++){
    for (int c = 0; c < N_1; c++){
      sum1 = 0;
      for (int v = 0; v < N_1; v++){
        sum1 += A_1[r][v] * B_1[v][c];
      }
      C_1[r][c] = sum1;
    }
  }

  t1 = (micros() - t1);

  Serial.print("Time required (microseconds): ");
  Serial.println(t1);
}
