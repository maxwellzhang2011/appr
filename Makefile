CC = clang
CFLAGS = -lglfw -lGL -lm -g
CFILES = src/main.c src/load_apps.c src/split.c
INSTALL_ALLOW=0
UNINSTALL_ALLOW=0

all:
	$(CC) $(CFLAGS) $(CFILES) -o release/appr
	@ echo 'output at: release/arp'

run:
	@./release/appr

install:
	@ echo '!!!WARNING: THIS IS STILL IN ALPHA VERSION'
	@ if [ "$(INSTALL_ALLOW)" = "1" ]; then \
		chmod +x release/appr; \
		sudo mv release/appr /usr/local/bin/; \
	else \
		echo 'add INSTALL_ALLOW=1 as a make flag'; \
	fi

uninstall:
	@ if [ "$(UNINSTALL_ALLOW)" = "1" ]; then \
		sudo rm /usr/local/bin/appr; \
	else \
		echo 'add UNINSTALL_ALLOW=1 as a make flag'; \
	fi
