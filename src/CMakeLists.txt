CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)
include_directories(./)
SET(SOURCES 
main.cpp 
./Model/Entities/Entity.cpp
./Model/Entities/Friendly.cpp 
./Model/Entities/Enemy.cpp  
./Model/Entities/Neutral.cpp 
./Model/Entities/Player.cpp 
./Model/Entities/PlayerBullet.cpp 
./Model/Entities/Background.cpp 
./Model/Entities/Border.cpp
./Model/Entities/EnemyBullet.cpp
./Model/Entities/EnemyLaser.cpp 
./Model/Entities/EnemyGrunt.cpp 
./Model/Entities/FlyingSaucer.cpp  
./Model/Entities/FlyingObstacle.cpp
./Model/Entities/EnemyShooter.cpp 
./Model/Entities/SaucerBoss.cpp
./Model/Entities/ShooterBoss.cpp
./Model/Entities/CrystalBoss.cpp  
./Model/EntityFactory.cpp 
./Model/Events.cpp 
./Model/EventQueue.cpp 
./Model/PlayerData.cpp
./Model/Model.cpp
./View/Animation.cpp 
./View/StatusDisplay.cpp 
./View/View.cpp  
./Controller/Controller.cpp 
./Utilities/Transformation.cpp 
./Utilities/Stopwatch.cpp
./Game/Scoreboard.cpp
./Game/Game.cpp
)

ADD_EXECUTABLE(Gradius ${SOURCES})
TARGET_LINK_LIBRARIES(Gradius -lsfml-graphics -lsfml-window -lsfml-system)

INSTALL(TARGETS Gradius RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

