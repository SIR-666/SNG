void supply_wire_process()
{
  
  while(tray_scan==false)
  {
    lcd.setCursor(0, 0);
    lcd.print("   SCAN TRAY   ");
    scan_tray();
  }

    wire_scann();
}
