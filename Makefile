PACKAGES = sdl2 SDL2_mixer SDL2_image
LDLIBS = -lm
CFLAGS = -Wall -Wno-unused-function

ifeq ($(OS), Windows_NT)
   LDLIBS += -lopengl32 -mwindows
else
   PACKAGES += gl
endif

CFLAGS += $(shell pkg-config --cflags $(PACKAGES))
LDLIBS += $(shell pkg-config --libs $(PACKAGES))

TuesTycoon: Main.cpp drawfunc.cpp gui.cpp
	g++ $(CFLAGS) -o $@ $< $(LDLIBS)
