PACKAGES = sdl2 SDL2_mixer SDL2_image
LDLIBS = -lm
CFLAGS = -Wall

ifeq ($(OS), Windows_NT)
   LDLIBS += -lopengl32 -mwindows
else
   PACKAGES += gl
endif

CFLAGS += $(shell pkg-config --cflags $(PACKAGES))
LDLIBS += $(shell pkg-config --libs $(PACKAGES))

bin/TuesTycoon: Main.cpp
	g++ $(CFLAGS) -o $@ $< $(LDLIBS)
