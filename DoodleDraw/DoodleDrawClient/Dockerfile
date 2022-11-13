FROM vookimedlo/ubuntu-qt:qt6_latestDistroOfficial_gcc_kinetic

RUN sudo apt-get update \
  && sudo apt-get install --yes \
    -qqy x11-apps \
    vim gedit tar wget \
    qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qt5-image-formats-plugins qtwayland5 qtchooser qt5-qmake qtdeclarative5-dev \
    qtbase5-dev-tools qt5-image-formats-plugins qtwayland5 qtdeclarative5-dev \
    default-libmysqlclient-dev \
    libxkbcommon-dev libqt5websockets5-dev libxcb-xinerama0 libx11-xcb-dev libxkbcommon-dev libqt5websockets5-dev libxcb-xinerama0 \
    libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libqt5gui5 libxext-dev libxext-doc libxtst-dev \
    qml-module-qtquick-controls2 qml-module-qtquick2 qml-module-qtquick-window2 libqt5qml5

ENV QT_QPA_PLATFORM=xcb

ENV DISPLAY=host.docker.internal:0.0

EXPOSE 800

WORKDIR /tmp/DoodleDraw/

COPY . .

RUN qmake
RUN make

CMD ["./DoodleDrawClient"]


