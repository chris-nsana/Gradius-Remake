include_directories(./)
SET(SOURCES main.cpp  ./View/Animation.cpp ./Model/Entities/Entity.cpp ./Model/Entities/Neutral.cpp ./Model/Entities/Friendly.cpp ./Model/Entities/Enemy.cpp ./Model/Entities/Player.cpp ./Model/Entities/PlayerBullet.cpp ./Model/Entities/Background.cpp ./Model/Entities/Border.cpp ./Game.cpp ./Model/Model.cpp ./Controller/Controller.cpp ./View/View.cpp ./Utilities/Transformation.cpp ./Utilities/Stopwatch.cpp)

ADD_EXECUTABLE(Gradius ${SOURCES})
TARGET_LINK_LIBRARIES(Gradius -lsfml-graphics -lsfml-window -lsfml-system)

INSTALL(TARGETS Gradius RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

