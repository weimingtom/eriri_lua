require 'printf.lua'
printf("Hello %s from %s on %s\n",os.getenv"USER" or "there",_VERSION,os.date())
