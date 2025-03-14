// Lupi DPI Bypass 2.0.1
// Development for Windows (x64)

// Use -- <sh compile.sh> -- in your terminal to compile (Linux/MacOS) (Powered by CMake)
// Use -- <qmake main.pro & mingw32-make> -- in your cmd to compile (Windows) (Powered by QMake)

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QEvent>
#include <QPainter>
#include <QStyleOption>
#include <QIcon>
#include <QProcess>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

class LupiDPI : public QWidget {

    Q_OBJECT

public:
    explicit LupiDPI( QWidget *parent = nullptr );

protected:
    bool eventFilter( QObject *obj, QEvent *event ) override;

private:
    void animateButton( QPushButton *button, const QColor &hoverColor );
    void executeCommand( const QString &command );
};

LupiDPI::LupiDPI( QWidget *parent ) : QWidget( parent ) {

    setFixedSize( 320, 520 );
    setWindowTitle( "Lupi DPI Bypass" );
    setWindowIcon( QIcon( ":/icon.ico" ));

    setStyleSheet( R"(
        QWidget {
            background-color: #2E3440;
            color: #ECEFF4;
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
        }
        QPushButton {
            background-color: #4C566A;
            color: #ECEFF4;
            border-radius: 8px;
            padding: 12px;
            border: none;
            font-weight: bold;
            transition: background-color 0.3s ease;
        }
        QPushButton:hover {
            background-color: #5E81AC;
        }
        QPushButton:pressed {
            background-color: #81A1C1;
        }
        QComboBox {
            background-color: #4C566A;
            color: #ECEFF4;
            border: 1px solid #5E81AC;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
            min-height: 30px;
        }
        QComboBox:hover {
            border-color: #81A1C1;
        }
        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 30px;
            border-left: 1px solid #5E81AC;
            border-radius: 0 8px 8px 0;
        }
        QComboBox::down-arrow {
            image: url(:/icons/arrow-down.png); /* Можно заменить на свою стрелку */
            width: 12px;
            height: 12px;
        }
        QComboBox QAbstractItemView {
            background-color: #4C566A;
            color: #ECEFF4;
            border: 1px solid #5E81AC;
            border-radius: 8px;
            padding: 8px;
            selection-background-color: #5E81AC;
            selection-color: #ECEFF4;
        }
        QComboBox QAbstractItemView::item {
            padding: 8px;
            border-radius: 4px;
        }
        QComboBox QAbstractItemView::item:hover {
            background-color: #5E81AC;
            color: #ECEFF4;
        }
    )" );

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout -> setContentsMargins( 20, 15, 20, 15 );
    layout -> setSpacing( 10 );

    QPushButton *startBtn = new QPushButton( "Launch DPI Bypass" );
    startBtn -> setCursor( Qt::PointingHandCursor );

    QComboBox *altStarts = new QComboBox();
    altStarts -> addItem( "Default (Russia)", "general.bat" );
    altStarts -> addItem( "Default (Iran)", "iran.bat" );
    altStarts -> addItem( "Alt Launch 1", "alt1.bat" );
    altStarts -> addItem( "Alt Launch 2", "alt2.bat" );
    altStarts -> addItem( "Alt Launch 3", "alt3.bat" );
    altStarts -> addItem( "Alt Launch 4", "alt4.bat" );

    QPushButton *installBtn = new QPushButton( "Install Bypass Service" );
    QPushButton *removeBtn = new QPushButton( "Remove Bypass Service" );

    QPushButton *addressBtn = new QPushButton( "Open Address List" );
    QPushButton *openBtn = new QPushButton( "Open Bin Folder" );
    QPushButton *infoBtn = new QPushButton( "Guide" );

    installBtn -> setCursor( Qt::PointingHandCursor );
    removeBtn -> setCursor( Qt::PointingHandCursor );
    addressBtn -> setCursor( Qt::PointingHandCursor );
    openBtn -> setCursor( Qt::PointingHandCursor );
    infoBtn -> setCursor( Qt::PointingHandCursor );

    layout -> addWidget( startBtn );
    layout -> addWidget( altStarts );
    layout -> addSpacing( 20 );
    layout -> addWidget( installBtn );
    layout -> addWidget( removeBtn );
    layout -> addSpacing( 20 );
    layout -> addWidget( addressBtn );
    layout -> addSpacing( 20 ); 
    layout -> addWidget( openBtn );
    layout -> addWidget( infoBtn );

    altStarts -> setVisible( true );

    connect( infoBtn, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl( QUrl::fromLocalFile( QDir::currentPath() + "/guide.html" ) );
    } );

    connect( openBtn, &QPushButton::clicked, this, []() {
        system( "explorer.exe DPI" );
    } );

    connect( addressBtn, &QPushButton::clicked, this, []() {
        QDesktopServices::openUrl( QUrl::fromLocalFile( QDir::currentPath() + "/DPI/list-general.txt" ) );
    } );

    connect( startBtn, &QPushButton::clicked, [startBtn, installBtn, 
            removeBtn, addressBtn, openBtn, altStarts, this]() {
        QString selectedBatFile = altStarts -> currentData().toString();
        executeCommand( "cd DPI & " + selectedBatFile );
    } );

    connect( installBtn, &QPushButton::clicked, this, [this]() {
        system( "cd DPI & service_install.bat" );
    } );

    connect( removeBtn, &QPushButton::clicked, this, [this]() {
        system( "cd DPI & service_remove.bat" );
    } );

    startBtn -> installEventFilter( this );
    installBtn -> installEventFilter( this );
    removeBtn -> installEventFilter( this );
    addressBtn -> installEventFilter( this );
    openBtn -> installEventFilter( this );
    infoBtn -> installEventFilter( this );
}

bool LupiDPI::eventFilter( QObject *obj, QEvent *event ) {
    if ( event -> type() == QEvent::Enter ) {
        if (QPushButton *button = qobject_cast<QPushButton*>( obj )) {
            animateButton( button, QColor( 94, 129, 172 ));
        }
    } else if (event -> type() == QEvent::Leave) {
        if (QPushButton *button = qobject_cast<QPushButton*>( obj )) {
            animateButton( button, QColor( 76, 86, 106 ));
        }
    }
    return QWidget::eventFilter( obj, event );
}

void LupiDPI::animateButton( QPushButton *button, const QColor &targetColor ) {
    QPropertyAnimation *animation = new QPropertyAnimation( button, "backgroundColor" );
    animation -> setDuration( 300 );
    animation -> setStartValue( button -> palette().button().color() );
    animation -> setEndValue( targetColor );
    animation -> start( QAbstractAnimation::DeleteWhenStopped );
}

void LupiDPI::executeCommand( const QString &command ) {
    QString fullPath = QDir::currentPath() + "/DPI/" + command;
    qDebug() << "Executing command:" << fullPath;

    QProcess *process = new QProcess( this );
    process -> setWorkingDirectory( QDir::currentPath() + "/DPI" );
    process -> start( "cmd.exe", { "/c", command } );

    connect( process, QOverload<QProcess::ProcessError>::of( &QProcess::errorOccurred ), []( QProcess::ProcessError error ) {
        QMessageBox::critical( nullptr, "Error", "Failed to execute the command." );
    } );
}

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );
    LupiDPI window;
    window.show();
    return app.exec();
}

#include "main.moc"
