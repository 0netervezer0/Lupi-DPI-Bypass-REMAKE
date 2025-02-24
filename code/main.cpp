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

class LupiDPI : public QWidget {

    Q_OBJECT

public:
    explicit LupiDPI( QWidget *parent = nullptr );

protected:
    bool eventFilter( QObject *obj, QEvent *event ) override;

private:
    void animateButton( QPushButton *button, const QColor &hoverColor );
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
    QPushButton *stopBtn = new QPushButton( "Stop DPI Bypass" );

    QPushButton *addressBtn = new QPushButton( "Open Address List" );
    QPushButton *openBtn = new QPushButton( "Open Bin Folder" );
    QPushButton *infoBtn = new QPushButton( "Guide" );

    installBtn -> setCursor( Qt::PointingHandCursor );
    removeBtn -> setCursor( Qt::PointingHandCursor );
    stopBtn -> setCursor( Qt::PointingHandCursor );
    addressBtn -> setCursor( Qt::PointingHandCursor );
    openBtn -> setCursor( Qt::PointingHandCursor );
    infoBtn -> setCursor( Qt::PointingHandCursor );

    layout -> addWidget( startBtn );
    layout -> addWidget( altStarts );
    layout -> addSpacing( 20 );
    layout -> addWidget( installBtn );
    layout -> addWidget( removeBtn );
    layout -> addSpacing( 20 );
    layout -> addWidget( stopBtn );
    layout -> addWidget( addressBtn );
    layout -> addSpacing( 20 ); 
    layout -> addWidget( openBtn );
    layout -> addWidget( infoBtn );

    stopBtn -> setVisible( false );
    altStarts -> setVisible( true );

    connect( infoBtn, &QPushButton::clicked, this, []() {
        QMessageBox::information( nullptr, "Guide", "Guide" );
    } );

    connect( openBtn, &QPushButton::clicked, this, []() {
        // 
    } );

    connect( addressBtn, &QPushButton::clicked, this, []() {
        // 
    } );

    connect( startBtn, &QPushButton::clicked, [startBtn, stopBtn, installBtn, 
            removeBtn, addressBtn, openBtn, altStarts]() {
        startBtn -> setVisible( false ); 
        stopBtn -> setVisible( true ); 

        installBtn -> setVisible( false );
        removeBtn -> setVisible( false );
        addressBtn -> setVisible( false );
        openBtn -> setVisible( false );
        
        altStarts->setVisible( false );
    } );

    connect( stopBtn, &QPushButton::clicked, [startBtn, stopBtn, installBtn, 
            removeBtn, addressBtn, openBtn, altStarts]() {
        startBtn -> setVisible( true );
        stopBtn -> setVisible( false );

        installBtn -> setVisible( true );
        removeBtn -> setVisible( true );
        addressBtn -> setVisible( true );
        openBtn -> setVisible( true );

        altStarts->setVisible( true );
    } );

    startBtn -> installEventFilter( this );
    installBtn -> installEventFilter( this );
    removeBtn -> installEventFilter( this );
    stopBtn -> installEventFilter( this );
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

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );
    LupiDPI window;
    window.show();
    return app.exec();
}

#include "main.moc"