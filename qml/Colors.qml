import QtQuick

QtObject {
    property bool isDark: false

    readonly property color windowBackground:
        isDark ? "#4B5E74" : "#EAF3FC"

    readonly property color itemBackground:
        isDark ? "#3A4A5F" : "#FFFFFF"

    readonly property color primaryText:
        isDark ? "#F5F5F7" : "#1D1D1F"

    readonly property color accentColor:
        isDark ? "#64B5FF" : "#40A3FF"

    readonly property color separator:
        isDark ? "#405064" : "#D5E1EF"
}
