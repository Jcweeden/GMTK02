#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Game.cpp I_GameObject.cpp GameObject.cpp InputHandler.cpp TextureManager.cpp CollisionManager.cpp SoundMixer.cpp PlayState.cpp Ball.cpp Block.cpp Shooter.cpp

#CC specifies which compiler we're using
CC = g++ -std=c++11

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = SushiSmash

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
