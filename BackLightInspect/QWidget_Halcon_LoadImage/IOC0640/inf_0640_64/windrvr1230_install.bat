@ECHO OFF
cd %~dp0
wdreg -inf windrvr1230_driver.inf install
if exist IOC0640.inf (
  wdreg -inf IOC0640.inf install
)

