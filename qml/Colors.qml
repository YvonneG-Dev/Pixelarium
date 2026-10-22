import QtQuick

QtObject {
    property bool isDark: false


    // property color reallyDark: "#1f1f1f"
    // property color dark: "#262626"
    // property color reallyLight: "#e7e7e7"
    // property color light: "#e0e0e0"

    readonly property color windowBackground:
        isDark ? "#202A38" : "#EAF3FC"


    readonly property color itemBackground:
        isDark ? "#2B3748" : "#FFFFFF"

    readonly property color primaryText:
        isDark ? "#F5F5F7" : "#1D1D1F"

    readonly property color accentColor:
        isDark ? "#64B5FF" : "#40A3FF"

    readonly property color buttonBackground:
        isDark ? "#354357" : "#FFFFFF"

    readonly property color buttonBorder:
        isDark ? "#506078" : "#C7D8EA"
}
