#define N_0 16

int A_0[N_0][N_0], B_0[N_0][N_0], C_0[N_0][N_0];
unsigned long t0 = 0;
long int sum0;

void setup_0(){
  Serial.println("Core 0 initializing");
}

void loop_0(){
  
  for (int r = 0; r < N_0; r++){
    for (int c = 0; c < N_0; c++){
      A_0[r][c] = random(0, 100);
      B_0[r][c] = random(0, 100);
    }
  }

  t0 = micros();

  for (int r = 0; r < N_0; r++){
    for (int c = 0; c < N_0; c++){
      sum0 = 0;
      for (int v = 0; v < N_0; v++){
        sum0 += A_0[r][v] * B_0[v][c];
      }
      C_0[r][c] = sum0;
    }
  }

  t0 = (micros() - t0);

  Serial.print("Time required (microseconds): ");
  Serial.println(t0);
}
