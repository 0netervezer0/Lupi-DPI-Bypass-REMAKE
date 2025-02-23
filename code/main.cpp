#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>

class LupiDPI : public QWidget {

    Q_OBJECT

public:
    explicit LupiDPI( QWidget *parent = nullptr );

};


LupiDPI::LupiDPI( QWidget *parent ) : QWidget( parent ) {

    setFixedSize( 320, 400 );
    setWindowTitle( "Lupi DPI Bypass" );
    setStyleSheet( "background-color: #444A4B;" );

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout -> setSpacing( -50 );
    layout -> setContentsMargins( 15, 10, 15, 10 );

    QPushButton *startBtn = new QPushButton( "Launch DPI Bypass" );
    QPushButton *installBtn = new QPushButton( "Install Bypass Service" );
    QPushButton *removeBtn = new QPushButton( "Remove Bypass Service" );
    QPushButton *stopBtn = new QPushButton( "Stop DPI Bypass" );
    QPushButton *infoBtn = new QPushButton( "Guide" );

    startBtn -> setStyleSheet( "background-color: #33A3AD; color: white; border-radius: 10px; padding: 14px;" );
    installBtn -> setStyleSheet( "background-color: #33A3AD; color: white; border-radius: 10px; padding: 10px;" );
    removeBtn -> setStyleSheet( "background-color: #33A3AD; color: white; border-radius: 10px; padding: 10px;" );
    stopBtn -> setStyleSheet( "background-color: #33A3AD; color: white; border-radius: 10px; padding: 10px;" );
    infoBtn -> setStyleSheet( "background-color: #3e8790; color: white; border-radius: 10px; padd ing: 10px;" );

    QComboBox *altStarts = new QComboBox();
    altStarts -> addItem( "Default (Russia)", "general.bat" );
    altStarts -> addItem( "Default (Iran)", "iran.bat" );
    altStarts -> addItem( "Alt Launch 1", "alt1.bat" );
    altStarts -> addItem( "Alt Launch 2", "alt2.bat" );
    altStarts -> addItem( "Alt Launch 3", "alt3.bat" );
    altStarts -> addItem( "Alt Launch 4", "alt4.bat" );
    altStarts -> setStyleSheet( "background-color: #444A4B; border: 1px solid #ccc; border-radius: 5px; padding: 8px;\
        padding-left: 8px; padding-right: 8px;" );

    layout -> addWidget( startBtn );
    layout -> addWidget( altStarts );
    layout -> addWidget( installBtn );
    layout -> addWidget( removeBtn );
    layout -> addWidget( stopBtn );
    layout -> addWidget( infoBtn );

    stopBtn -> setVisible( false );
    altStarts -> setVisible( true );

    connect( infoBtn, &QPushButton::clicked, this, []() {
        QMessageBox::information( nullptr, "Guide", "Инструкция по использованию..." );
    } );

    connect( startBtn, &QPushButton::clicked, [startBtn, stopBtn, installBtn, removeBtn, altStarts]() {
        startBtn -> setVisible( false ); 
        stopBtn -> setVisible( true ); 

        installBtn -> setVisible( false );
        removeBtn -> setVisible( false );
        
        altStarts -> setVisible( false );
    } );

    connect( stopBtn, &QPushButton::clicked, [startBtn, stopBtn, installBtn, removeBtn, altStarts]() {
        startBtn -> setVisible( true );
        stopBtn -> setVisible( false );

        installBtn -> setVisible( true );
        removeBtn -> setVisible( true );

        altStarts -> setVisible( true );
    } );

}


int main( int argc, char *argv[] ) {

    QApplication app( argc, argv );
    LupiDPI window;
    window.show();
    return app.exec();

}

#include "main.moc"
