void reset_manual() {
  digitalWrite(RES, LOW);
  delay(1000);
  digitalWrite(RES, HIGH);
  delay(2000);
  digitalWrite(RESET_MACHIN, LOW);
  delay(1000);
  digitalWrite(RESET_MACHIN, HIGH);
  delay(10);
  digitalWrite(RESET_MACHIN, LOW);
  delay(1000);
  digitalWrite(RESET_MACHIN, HIGH);
  digitalWrite(RES, HIGH);
}
