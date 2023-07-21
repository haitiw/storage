cmd_/home/siri/Linux_4412/storage/dev/leddev.mod := printf '%s\n'   leddev.o | awk '!x[$$0]++ { print("/home/siri/Linux_4412/storage/dev/"$$0) }' > /home/siri/Linux_4412/storage/dev/leddev.mod
