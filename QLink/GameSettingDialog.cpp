#include "GameSettingDialog.h"
#include "ui_GameSettingDialog.h"

GameSettingDialog::GameSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSettingDialog)
{
    ui->setupUi(this);

    ui->widthSpinBox->setValue(6);
    ui->heightSpinBox->setValue(6);

    QApplication::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &GameSettingDialog::checkAndStart);
}

GameSettingDialog::~GameSettingDialog()
{
    delete ui;
}

bool GameSettingDialog::checkValidation() {
    return ui->widthSpinBox->value() % 2 == 0 || ui->heightSpinBox->value() % 2 == 0;
}

void GameSettingDialog::setGameMode(GameMode gameMode) {
    this->gameMode = gameMode;
}

void GameSettingDialog::checkAndStart() {
    if (!checkValidation())
        QMessageBox::warning(this, "警告", "宽或高必须为整数！");
    else {
        emit startGame(ui->widthSpinBox->value(), ui->heightSpinBox->value(), gameMode);
        close();
    }
}
