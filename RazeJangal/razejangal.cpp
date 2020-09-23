#include <time.h>
#include <fstream>
#include "razejangal.h"
#include <rolldialog.h>
#include <QMessageBox>
#include "ui_razejangal.h"
#include <QPixmap>
#include <setplayerdialog.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include "dragwidget.h"
#include <QObject>
#include "mainwindow.h"

using namespace std;

RazeJangal::RazeJangal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RazeJangal)
{
    ui->setupUi(this);
    set_vectors();
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    try{
        SetPlayerDialog new_set_player(this, &number_of_players, &player_names);
        new_set_player.setModal(true);
        new_set_player.exec();
    }
    catch(QString exception){
        throw exception;
    }



    ui->First_dice_1->setVisible(false);
    ui->Second_dice_1->setVisible(false);
    ui->First_dice_2->setVisible(false);
    ui->Second_dice_2->setVisible(false);
    ui->First_dice_3->setVisible(false);
    ui->Second_dice_3->setVisible(false);
    ui->First_dice_4->setVisible(false);
    ui->Second_dice_4->setVisible(false);
    ui->Change_treasure->setVisible(false);
}


void RazeJangal::redcell_options(){
    QPixmap yellow_Orange_cell_png(":/resources/PNG/Yellow_Orange.png");
    QIcon yellow_Orange_cell(yellow_Orange_cell_png);

    this->new_game.get_red_cell_options();

    for(int i = 0; i < this->new_game.orange_cell_ID().size(); i++){
        int ID = this->new_game.orange_cell_ID()[i] ;
        this->cells[ID - 1]->setIcon(yellow_Orange_cell);
    }

    ui->Dont_guess->setVisible(true);
    ui->Dont_guess->setText("نمی‌خوام حدس بزنم");
}

void RazeJangal::set_round(){
    this->new_game.new_round();

    QString round = "مرحله ";
    round += QString::number(this->new_game.get_current_round());
    this->ui->Round_Info->setText(round);
    this->ui->Round_Info->setStyleSheet("font-size: 22pt; color : black");

    QString treasure_info = "گنج این مرحله: ";
    treasure_info += this->new_game.get_current_treasure();
    ui->Treasure_Info->setText(treasure_info);
    ui->Treasure_Info->setStyleSheet("font-size: 14pt");

    for(int i = 0; i < this->number_of_players; i++){
        QString text = this->player_names[i];
        text += "\n";
        text += "امتیاز: " + QString::number(this->new_game.get_treasure_num(i));
        this->player_info[i]->setText(text);
        this->player_info[i]->setStyleSheet("font-size: 14pt; color : black");
    }

    this->player_info[this->new_game.get_current_player_ID() - 1]->setStyleSheet("font-size: 17pt; color : red");
    QString message = "مرحله‌ی ";
    message += QString::number(this->new_game.get_current_round());
    message += " شروع شد";
    QMessageBox::information(this,"مرحله جدید", message, QMessageBox::Ok);
}

void RazeJangal::set_map(){
    QPixmap blue_cell_png(":/resources/PNG/Blue.png");
    QIcon blue_cell(blue_cell_png);
    QPixmap green_cell_png(":/resources/PNG/Green.png");
    QIcon green_cell(green_cell_png);
    QPixmap orange_cell_png(":/resources/PNG/Orange.png");
    QIcon orange_cell(orange_cell_png);
    QPixmap violet_cell_png(":/resources/PNG/Violet.png");
    QIcon violet_cell(violet_cell_png);
    QPixmap red_cell_png(":/resources/PNG/Red.png");
    QIcon red_cell(red_cell_png);
    QPixmap player_1_png(":/resources/PNG/player_1.png");
    QIcon player_1(player_1_png);
    QPixmap player_2_png(":/resources/PNG/player_2.png");
    QIcon player_2(player_2_png);
    QPixmap player_3_png(":/resources/PNG/player_3.png");
    QIcon player_3(player_3_png);
    QPixmap player_4_png(":/resources/PNG/player_4.png");
    QIcon player_4(player_4_png);

    ifstream myfile (this->address + "newpositions.txt");
    if (myfile.is_open())
    {
        int number, X, Y, aux = 0;
        string color;

        while (myfile >> number) {
            myfile >> X >> Y >> color;
            this->cells[number - 1]->move(X, Y);
            if(color == "red"){
                this->cells[number - 1]->setIcon(red_cell);
            }
            if(color == "orange")
                this->cells[number - 1]->setIcon(orange_cell);
            if(color == "violet")
                this->cells[number - 1]->setIcon(violet_cell);
            if(color == "green")
                this->cells[number - 1]->setIcon(green_cell);
        }
        myfile.close();
        aux = number;
        for(int o = aux + 1;o <= 116;o++){
            this->cells[o - 1]->setVisible(false);
        }
    }
    else cout << "Unable to open file";

//    std::fstream myfile;
//        myfile.open (":/resources/newpositions.txt", std::ios::in);


    for(int i = 0; i < 4; i++){
        this->blue_cells[i]->setIcon(blue_cell);
    }

//    int k = 0;
//    for(int i = 0; i < 116; i++){
//        if(i + 1 == this->new_game.red_cell_ID()){
//            this->cells[i]->setIcon(red_cell);
//        }
//        else if(i + 1 == this->new_game.violet_cell_ID()){
//            this->cells[i]->setIcon(violet_cell);
//        }
//        else if(i + 1 == this->new_game.orange_cell_ID()[k]){
//            this->cells[i]->setIcon(orange_cell);
//            k++;
//        }
//        else{
//            this->cells[i]->setIcon(green_cell);
//        }
//    }

    if(this->new_game.get_position(0) < 0)
        this->blue_cells[0]->setIcon(player_1);
    else
        this->cells[this->new_game.get_position(0) - 1]->setIcon(player_1);

    if(this->new_game.get_position(1) < 0)
        this->blue_cells[1]->setIcon(player_2);
    else
        this->cells[this->new_game.get_position(1) - 1]->setIcon(player_2);

    if(number_of_players > 2){
        if(this->new_game.get_position(2) < 0)
            this->blue_cells[2]->setIcon(player_3);
        else
            this->cells[this->new_game.get_position(2) - 1]->setIcon(player_3);

        if(number_of_players > 3){
            if(this->new_game.get_position(3) < 0)
                this->blue_cells[3]->setIcon(player_4);
            else
                this->cells[this->new_game.get_position(3) - 1]->setIcon(player_4);
        }
    }

    this->ui->Change_treasure->setVisible(false);
    this->ui->Dont_guess->setVisible(false);
}

void RazeJangal::set_vectors(){
    this->blue_cells.push_back(ui->BlueCell_1);
    this->blue_cells.push_back(ui->BlueCell_2);
    this->blue_cells.push_back(ui->BlueCell_3);
    this->blue_cells.push_back(ui->BlueCell_4);

    this->cells.push_back(ui->Cell_1);
    this->cells.push_back(ui->Cell_2);
    this->cells.push_back(ui->Cell_3);
    this->cells.push_back(ui->Cell_4);
    this->cells.push_back(ui->Cell_5);
    this->cells.push_back(ui->Cell_6);
    this->cells.push_back(ui->Cell_7);
    this->cells.push_back(ui->Cell_8);
    this->cells.push_back(ui->Cell_9);
    this->cells.push_back(ui->Cell_10);
    this->cells.push_back(ui->Cell_11);
    this->cells.push_back(ui->Cell_12);
    this->cells.push_back(ui->Cell_13);
    this->cells.push_back(ui->Cell_14);
    this->cells.push_back(ui->Cell_15);
    this->cells.push_back(ui->Cell_16);
    this->cells.push_back(ui->Cell_17);
    this->cells.push_back(ui->Cell_18);
    this->cells.push_back(ui->Cell_19);
    this->cells.push_back(ui->Cell_20);
    this->cells.push_back(ui->Cell_21);
    this->cells.push_back(ui->Cell_22);
    this->cells.push_back(ui->Cell_23);
    this->cells.push_back(ui->Cell_24);
    this->cells.push_back(ui->Cell_25);
    this->cells.push_back(ui->Cell_26);
    this->cells.push_back(ui->Cell_27);
    this->cells.push_back(ui->Cell_28);
    this->cells.push_back(ui->Cell_29);
    this->cells.push_back(ui->Cell_30);
    this->cells.push_back(ui->Cell_31);
    this->cells.push_back(ui->Cell_32);
    this->cells.push_back(ui->Cell_33);
    this->cells.push_back(ui->Cell_34);
    this->cells.push_back(ui->Cell_35);
    this->cells.push_back(ui->Cell_36);
    this->cells.push_back(ui->Cell_37);
    this->cells.push_back(ui->Cell_38);
    this->cells.push_back(ui->Cell_39);
    this->cells.push_back(ui->Cell_40);
    this->cells.push_back(ui->Cell_41);
    this->cells.push_back(ui->Cell_42);
    this->cells.push_back(ui->Cell_43);
    this->cells.push_back(ui->Cell_44);
    this->cells.push_back(ui->Cell_45);
    this->cells.push_back(ui->Cell_46);
    this->cells.push_back(ui->Cell_47);
    this->cells.push_back(ui->Cell_48);
    this->cells.push_back(ui->Cell_49);
    this->cells.push_back(ui->Cell_50);
    this->cells.push_back(ui->Cell_51);
    this->cells.push_back(ui->Cell_52);
    this->cells.push_back(ui->Cell_53);
    this->cells.push_back(ui->Cell_54);
    this->cells.push_back(ui->Cell_55);
    this->cells.push_back(ui->Cell_56);
    this->cells.push_back(ui->Cell_57);
    this->cells.push_back(ui->Cell_58);
    this->cells.push_back(ui->Cell_59);
    this->cells.push_back(ui->Cell_60);
    this->cells.push_back(ui->Cell_61);
    this->cells.push_back(ui->Cell_62);
    this->cells.push_back(ui->Cell_63);
    this->cells.push_back(ui->Cell_64);
    this->cells.push_back(ui->Cell_65);
    this->cells.push_back(ui->Cell_66);
    this->cells.push_back(ui->Cell_67);
    this->cells.push_back(ui->Cell_68);
    this->cells.push_back(ui->Cell_69);
    this->cells.push_back(ui->Cell_70);
    this->cells.push_back(ui->Cell_71);
    this->cells.push_back(ui->Cell_72);
    this->cells.push_back(ui->Cell_73);
    this->cells.push_back(ui->Cell_74);
    this->cells.push_back(ui->Cell_75);
    this->cells.push_back(ui->Cell_76);
    this->cells.push_back(ui->Cell_77);
    this->cells.push_back(ui->Cell_78);
    this->cells.push_back(ui->Cell_79);
    this->cells.push_back(ui->Cell_80);
    this->cells.push_back(ui->Cell_81);
    this->cells.push_back(ui->Cell_82);
    this->cells.push_back(ui->Cell_83);
    this->cells.push_back(ui->Cell_84);
    this->cells.push_back(ui->Cell_85);
    this->cells.push_back(ui->Cell_86);
    this->cells.push_back(ui->Cell_87);
    this->cells.push_back(ui->Cell_88);
    this->cells.push_back(ui->Cell_89);
    this->cells.push_back(ui->Cell_90);
    this->cells.push_back(ui->Cell_91);
    this->cells.push_back(ui->Cell_92);
    this->cells.push_back(ui->Cell_93);
    this->cells.push_back(ui->Cell_94);
    this->cells.push_back(ui->Cell_95);
    this->cells.push_back(ui->Cell_96);
    this->cells.push_back(ui->Cell_97);
    this->cells.push_back(ui->Cell_98);
    this->cells.push_back(ui->Cell_99);
    this->cells.push_back(ui->Cell_100);
    this->cells.push_back(ui->Cell_101);
    this->cells.push_back(ui->Cell_102);
    this->cells.push_back(ui->Cell_103);
    this->cells.push_back(ui->Cell_104);
    this->cells.push_back(ui->Cell_105);
    this->cells.push_back(ui->Cell_106);
    this->cells.push_back(ui->Cell_107);
    this->cells.push_back(ui->Cell_108);
    this->cells.push_back(ui->Cell_109);
    this->cells.push_back(ui->Cell_110);
    this->cells.push_back(ui->Cell_111);
    this->cells.push_back(ui->Cell_112);
    this->cells.push_back(ui->Cell_113);
    this->cells.push_back(ui->Cell_114);
    this->cells.push_back(ui->Cell_115);
    this->cells.push_back(ui->Cell_116);

    this->first_rolls.push_back(ui->First_dice_1);
    this->first_rolls.push_back(ui->First_dice_2);
    this->first_rolls.push_back(ui->First_dice_3);
    this->first_rolls.push_back(ui->First_dice_4);

    this->second_rolls.push_back(ui->Second_dice_1);
    this->second_rolls.push_back(ui->Second_dice_2);
    this->second_rolls.push_back(ui->Second_dice_3);
    this->second_rolls.push_back(ui->Second_dice_4);

    this->player_info.push_back(ui->Player_1);
    this->player_info.push_back(ui->Player_2);
    this->player_info.push_back(ui->Player_3);
    this->player_info.push_back(ui->Player_4);
}


RazeJangal::~RazeJangal()
{
    delete ui;
}

//
// Created by Omid on 7/4/2017.
//

int DicePool::random_roll() {
    return (rand() % 6) + 1;
}

DicePool::DicePool() {
    srand(time(NULL));

    //Loading dices from file
    int tmp;
    ifstream myfile (this->address + "SampleGame2DiceNumbers.txt");
    if (myfile.is_open())
    {
        while (myfile >> tmp)
        {
            this->numbers.resize(this->numbers.size() + 1);
            this->numbers[this->numbers.size() - 1] = tmp;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

int DicePool::roll_from_file() {
    int tmp = this->numbers[0];
    this->numbers.erase(this->numbers.begin());
    return tmp;
}

void RazeJangal::set_redcell_choice(int cell_ID){
    if(this->new_game.player_moved_to_red() && this->redcell_choice == 0 && !(this->dont_guess)){
        this->redcell_choice = cell_ID;
        this->set_map();
        redcell_wait.exit();
    }
    for(int i = 0; i < this->new_game.get_normal_available_cells().size(); i++){
        if(this->new_game.get_normal_available_cells()[i]->get_ID() == cell_ID && this->dont_guess){
            this->dont_guess = false;
        }
    }

    for(int i = 0; i < this->new_game.get_bonus_available_cells().size(); i++){
        if(this->new_game.get_bonus_available_cells()[i]->get_ID() == cell_ID && this->dont_guess){
            this->dont_guess = false;
        }
    }

}

void RazeJangal::set_choice(int cell_ID){
    for(int i = 0; i < this->new_game.get_normal_available_cells().size(); i++){
        if(this->new_game.get_normal_available_cells()[i]->get_ID() == cell_ID){
            this->new_game.clear_normal_available_cells();
            if(this->choice == 1)
                this->first_choice = cell_ID;
            else if(this->choice == 2)
                this->second_choice = cell_ID;
            this->set_map();
            this->normal_wait.exit();
            this->type_of_choice = 1;
        }
    }

    for(int i = 0; i < this->new_game.get_bonus_available_cells().size(); i++){
        if(this->new_game.get_bonus_available_cells()[i]->get_ID() == cell_ID){
            this->new_game.clear_bonus_available_cells();
            if(this->choice == 1)
                this->first_choice = cell_ID;
            this->set_map();
            this->normal_wait.exit();
            this->type_of_choice = 0;
        }
    }
}


void RazeJangal::second_cell_options(int first_choice){
    this->new_game.get_second_cell_options(first_choice);

    QPixmap yellow_cell_png(":/resources/PNG/Yellow.png");
    QIcon yellow_cell(yellow_cell_png);
    QPixmap yellow_Orange_cell_png(":/resources/PNG/Yellow_Orange.png");
    QIcon yellow_Orange_cell(yellow_Orange_cell_png);
    QPixmap yellow_Violet_cell_png(":/resources/PNG/Yellow_Violet.png");
    QIcon yellow_Violet_cell(yellow_Violet_cell_png);
    QPixmap yellow_Red_cell_png(":/resources/PNG/Yellow_Red.png");
    QIcon yellow_Red_cell(yellow_Red_cell_png);
    QPixmap yellow_Player1_cell_png(":/resources/PNG/Yellow_player_1.png");
    QIcon yellow_Player1_cell(yellow_Player1_cell_png);
    QPixmap yellow_Player2_cell_png(":/resources/PNG/Yellow_player_2.png");
    QIcon yellow_Player2_cell(yellow_Player2_cell_png);
    QPixmap yellow_Player3_cell_png(":/resources/PNG/Yellow_player_3.png");
    QIcon yellow_Player3_cell(yellow_Player3_cell_png);
    QPixmap yellow_Player4_cell_png(":/resources/PNG/Yellow_player_4.png");
    QIcon yellow_Player4_cell(yellow_Player4_cell_png);


    for(unsigned int i = 0; i < this->new_game.get_normal_available_cells().size(); i++){
        int ID = this->new_game.get_normal_available_cells()[i]->get_ID();

        if(this->new_game.get_normal_available_cells()[i]->get_color() == "Orange")
            this->cells[ID - 1]->setIcon(yellow_Orange_cell);

        else if(this->new_game.get_normal_available_cells()[i]->get_color() == "Red")
            this->cells[ID - 1]->setIcon(yellow_Red_cell);

        else if(this->new_game.get_normal_available_cells()[i]->get_color() == "Violet")
            this->cells[ID - 1]->setIcon(yellow_Violet_cell);

        else if(ID == this->new_game.get_position(0))
            this->cells[ID - 1]->setIcon(yellow_Player1_cell);

        else if(ID == this->new_game.get_position(1))
            this->cells[ID - 1]->setIcon(yellow_Player2_cell);

        else if(this->number_of_players > 2 && ID == this->new_game.get_position(2))
            this->cells[ID - 1]->setIcon(yellow_Player3_cell);

        else if(this->number_of_players > 3 && ID == this->new_game.get_position(3))
            this->cells[ID - 1]->setIcon(yellow_Player4_cell);

        else
            this->cells[ID - 1]->setIcon(yellow_cell);
    }
}

void RazeJangal::new_turn(int change_player){

    for(int i = 0; i < 4; i++){
        this->first_rolls[i]->setVisible(false);
        this->second_rolls[i]->setVisible(false);
    }

    for(int i = 0; i < this->number_of_players; i++){
        QString text = this->player_names[i];
        text += "\n";
        text += "امتیاز: " + QString::number(this->new_game.get_treasure_num(i));
        this->player_info[i]->setText(text);
        this->player_info[i]->setStyleSheet("font-size: 14pt; color : black");
    }

    this->new_game.change_player(change_player);
    this->new_game.clear_normal_available_cells();
    this->new_game.clear_bonus_available_cells();
    this->player_info[this->new_game.get_current_player_ID() - 1]->setStyleSheet("font-size: 17pt; color : red");
    int first_roll_number = this->new_game.roll_dice();
    int second_roll_number = this->new_game.roll_dice();

    RollDialog new_dialog(0, &first_roll_number, &second_roll_number);
    new_dialog.setModal(true);

    new_dialog.exec();
    this->new_game.set_current_player_rolls(first_roll_number,second_roll_number);

    this->new_game.get_new_turn_options();

    QString tmp1;
    QString tmp2;

    if(this->new_game.this_players_rolls().first == 1)
        tmp1 = ":/resources/PNG/one.png";
    else if(this->new_game.this_players_rolls().first == 2)
        tmp1 = ":/resources/PNG/two.png";
    else if(this->new_game.this_players_rolls().first == 3)
        tmp1 = ":/resources/PNG/three.png";
    else if(this->new_game.this_players_rolls().first == 4)
        tmp1 = ":/resources/PNG/four.png";
    else if(this->new_game.this_players_rolls().first == 5)
        tmp1 = ":/resources/PNG/five.png";
    else if(this->new_game.this_players_rolls().first == 6)
        tmp1 = ":/resources/PNG/six.png";

    if(this->new_game.this_players_rolls().second == 1)
        tmp2 = ":/resources/PNG/one.png";
    else if(this->new_game.this_players_rolls().second == 2)
        tmp2 = ":/resources/PNG/two.png";
    else if(this->new_game.this_players_rolls().second == 3)
        tmp2 = ":/resources/PNG/three.png";
    else if(this->new_game.this_players_rolls().second == 4)
        tmp2 = ":/resources/PNG/four.png";
    else if(this->new_game.this_players_rolls().second == 5)
        tmp2 = ":/resources/PNG/five.png";
    else if(this->new_game.this_players_rolls().second == 6)
        tmp2 = ":/resources/PNG/six.png";

    QPixmap first_roll(tmp1);
    QPixmap second_roll(tmp2);

    this->first_rolls[this->new_game.get_current_player_ID()-1]->setVisible(true);
    this->first_rolls[this->new_game.get_current_player_ID()-1]->setPixmap(first_roll);

    this->second_rolls[this->new_game.get_current_player_ID()-1]->setVisible(true);
    this->second_rolls[this->new_game.get_current_player_ID()-1]->setPixmap(second_roll);

    this->set_map();

    QPixmap yellow_cell_png(":/resources/PNG/Yellow.png");
    QIcon yellow_cell(yellow_cell_png);
    QPixmap yellow_Orange_cell_png(":/resources/PNG/Yellow_Orange.png");
    QIcon yellow_Orange_cell(yellow_Orange_cell_png);
    QPixmap yellow_Violet_cell_png(":/resources/PNG/Yellow_Violet.png");
    QIcon yellow_Violet_cell(yellow_Violet_cell_png);
    QPixmap yellow_Red_cell_png(":/resources/PNG/Yellow_Red.png");
    QIcon yellow_Red_cell(yellow_Red_cell_png);
    QPixmap yellow_Player1_cell_png(":/resources/PNG/Yellow_player_1.png");
    QIcon yellow_Player1_cell(yellow_Player1_cell_png);
    QPixmap yellow_Player2_cell_png(":/resources/PNG/Yellow_player_2.png");
    QIcon yellow_Player2_cell(yellow_Player2_cell_png);
    QPixmap yellow_Player3_cell_png(":/resources/PNG/Yellow_player_3.png");
    QIcon yellow_Player3_cell(yellow_Player3_cell_png);
    QPixmap yellow_Player4_cell_png(":/resources/PNG/Yellow_player_4.png");
    QIcon yellow_Player4_cell(yellow_Player4_cell_png);


    for(unsigned int i = 0; i < this->new_game.get_normal_available_cells().size(); i++){
        int ID = this->new_game.get_normal_available_cells()[i]->get_ID();

        if(this->new_game.get_normal_available_cells()[i]->get_color() == "Orange")
            this->cells[ID - 1]->setIcon(yellow_Orange_cell);

        else if(this->new_game.get_normal_available_cells()[i]->get_color() == "Red")
            this->cells[ID - 1]->setIcon(yellow_Red_cell);

        else if(this->new_game.get_normal_available_cells()[i]->get_color() == "Violet")
            this->cells[ID - 1]->setIcon(yellow_Violet_cell);

        else if(ID == this->new_game.get_position(0))
            this->cells[ID - 1]->setIcon(yellow_Player1_cell);

        else if(ID == this->new_game.get_position(1))
            this->cells[ID - 1]->setIcon(yellow_Player2_cell);

        else if(this->number_of_players > 2 && ID == this->new_game.get_position(2))
            this->cells[ID - 1]->setIcon(yellow_Player3_cell);

        else if(this->number_of_players > 3 && ID == this->new_game.get_position(3))
            this->cells[ID - 1]->setIcon(yellow_Player4_cell);

        else
            this->cells[ID - 1]->setIcon(yellow_cell);
    }

    for(unsigned int i = 0; i < this->new_game.get_bonus_available_cells().size(); i++){
        int ID = this->new_game.get_bonus_available_cells()[i]->get_ID();

        if(this->new_game.get_bonus_available_cells()[i]->get_color() == "Orange")
            this->cells[ID - 1]->setIcon(yellow_Orange_cell);

        else if(this->new_game.get_bonus_available_cells()[i]->get_color() == "Violet")
            this->cells[ID - 1]->setIcon(yellow_Violet_cell);

        else
            this->cells[ID - 1]->setIcon(yellow_cell);
    }

    if(this->new_game.this_players_rolls().first == this->new_game.this_players_rolls().second) {
        ui->Change_treasure->setText("اگه دوست داری گنج هدف این مرحله رو تغییر بدی منو بزن");
        ui->Change_treasure->setVisible(true);
    }
}

void RazeJangal::start_game() {
    // Set Info
    this->new_game.set_players(number_of_players);

    for(int q = 0; q < number_of_players; q++){
        this->new_game.set_players_name(player_names[q].toStdString(), q);
    }

    QString text;

    text = player_names[0];
    text += "\n";
    text += "امتیاز: " + QString::number(this->new_game.get_treasure_num(0));
    this->player_info[0]->setText(text);
    this->player_info[0]->setStyleSheet("font-size: 14pt; color : black");

    text = player_names[1];
    text += "\n";
    text += "امتیاز: " + QString::number(this->new_game.get_treasure_num(1));
    ui->Player_2->setText(text);
    ui->Player_2->setStyleSheet("font-size: 14pt; color : black");

    if(number_of_players < 4){
        ui->Divider_3->setVisible(false);
        ui->Player_4->setVisible(false);
        if(number_of_players < 3){
            ui->Divider_2->setVisible(false);
            ui->Player_3->setVisible(false);
        }
    }

    if(number_of_players > 2){
        text = player_names[2];
        text += "\n";
        text += "امتیاز: " + QString::number(this->new_game.get_treasure_num(2));
        ui->Player_3->setText(text);
        ui->Player_3->setStyleSheet("font-size: 14pt; color : black");
        if(number_of_players > 3){
            text = player_names[3];
            text += "\n";
            text += "امتیاز: " + QString::number(this->new_game.get_treasure_num(3));
            ui->Player_4->setText(text);
            ui->Player_4->setStyleSheet("font-size: 14pt; color : black");
        }
    }

    this->new_game.distribute_treasures();

    QString message1 = "آیا می خواهید نقشه را ویرایش کنید؟";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "آغاز", message1, QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        MainWindow *mapeditor1;
        mapeditor1 = new MainWindow(this, &editor_wait);
        mapeditor1->show();
        editor_wait.exec();
    }

    this->set_map();

    bool round_finished;
    bool change_player = false;
    bool last_player_won = false;

    for(int j = 1; j <= 13; j++) {
        round_finished = false;
        this->set_round();

        while(!round_finished){
            this->choice = 1;
            this->first_choice = 0;
            this->second_choice = 0;
            this->redcell_choice = 0;

            if(last_player_won) {
                this->redcell_options();
                redcell_wait.exec();

                if (redcell_choice > 0) {                      // if player wants to guess
                    int redcell_message_no = this->new_game.get_red_cell_message(redcell_choice);
                    this->set_map();
                    this->redcell_choice_message(redcell_message_no);

                    if (redcell_message_no == 1) {
                        last_player_won = true;
                        round_finished = true;
                        change_player = false;
                    } else {
                        last_player_won = false;
                        round_finished = false;
                        change_player = true;
                    }
                } else {
                    change_player = false;
                    last_player_won = false;
                    round_finished = false;
                }
            }

            if(!last_player_won) {
                this->redcell_choice = 0;
                this->new_turn(change_player);
                normal_wait.exec();
                int message_no = this->new_game.player_chose(this->first_choice, this->type_of_choice);
                this->choice_message(message_no);
                this->choice = 2;
                this->set_map();

                if (this->new_game.player_moved_to_red()) {
                    this->redcell_options();
                    redcell_wait.exec();

                    if (redcell_choice > 0) {                  // if player in red cell wants to guess
                        int redcell_message_no = this->new_game.get_red_cell_message(redcell_choice);
                        this->set_map();
                        this->redcell_choice_message(redcell_message_no);

                        if (redcell_message_no == 1) {
                            last_player_won = true;
                            round_finished = true;
                            change_player = false;
                        } else {
                            last_player_won = false;
                            round_finished = false;
                            change_player = true;
                        }
                    } else {
                        change_player = true;
                        last_player_won = false;
                        round_finished = false;
                    }
                }

                // if player wasn't in the red cell or he/she didn't want to guess
                // and he/she is available to have second move (in case that he/she had two similar dices and
                // he/she didn't chose to go to orange or violet cell or change the treasure)

                if (this->redcell_choice < 1 && this->type_of_choice == 1) {
                    this->second_cell_options(first_choice);

                    this->normal_wait.exec();
                    int message_no = this->new_game.player_chose(second_choice, 1);
                    this->choice_message(message_no);
                    this->set_map();

                    if (this->new_game.player_moved_to_red()) {
                        this->redcell_options();
                        redcell_wait.exec();

                        if (redcell_choice > 0) {
                            int redcell_message_no = this->new_game.get_red_cell_message(redcell_choice);
                            this->set_map();
                            this->redcell_choice_message(redcell_message_no);

                            if (redcell_message_no == 1) {
                                last_player_won = true;
                                round_finished = true;
                                change_player = false;
                            } else {
                                last_player_won = false;
                                round_finished = false;
                                change_player = true;
                            }
                        } else {
                            last_player_won = false;
                            round_finished = false;
                            change_player = true;
                        }
                    } else {
                        last_player_won = false;
                        round_finished = false;
                        change_player = true;
                    }
                }

//                // he/she had two similar dices and he/she chose to go to an orange or a violet cell or chose to change treasure
                else if(this->type_of_choice == 0 && redcell_choice < 1){
                    change_player = true;
                    round_finished = false;
                    last_player_won = false;
                }
            }
        }
    }

    int winners_point = 0;
    for(int i = 0; i < number_of_players; i++){
        if(this->new_game.get_treasure_num(i) > winners_point){
            winners_point = this->new_game.get_treasure_num(i);
        }
    }

    QString message;
    bool one_winner = true;
    message = "تبریک!\n";

    for(int i = 0; i < number_of_players; i++){
        if(this->new_game.get_treasure_num(i) == winners_point){
            message += this->player_names[i];
            if(one_winner){
                one_winner = false;
                message += "و ";
            }
            message += " ";
        }
    }

    message += "برنده شد";
    if(one_winner)
        message += "ند";

    QMessageBox::information(this, "پایان بازی", message, QMessageBox::Ok);
}

void RazeJangal::redcell_choice_message(int redcell_message_no){
    if(redcell_message_no != 0) {
        QString message = "همه‌ی بازیکنان به جز " + this->player_names[this->new_game.get_current_player_ID() - 1] + " چشمانشان را ببندند!";
        QMessageBox::warning(this, "اخظار", message, QMessageBox::Ok);

        message = " گنج خونه‌ی " + QString::number(this->redcell_choice) + "، " + this->new_game.get_treasure_name(this->redcell_choice);
        message += " هستش \n";
        QMessageBox::information(this,"مشاهده گنج", message, QMessageBox::Ok);

        if(redcell_message_no == 1){
            message = "حدس " + this->player_names[this->new_game.get_current_player_ID() - 1] + " (خانه‌ی " + QString::number(this->redcell_choice)
                    + ") درست بود و گنچ این مرحله (" + this->new_game.get_treasure_name(this->redcell_choice) + ") را به دست آورد.";
            QMessageBox::information(this,"برنده شدی :))", message, QMessageBox::Ok);
        }
        else if(redcell_message_no == 2){
            message = "حدس " + this->player_names[this->new_game.get_current_player_ID() - 1] + " (خانه‌ی " + QString::number(this->redcell_choice)
                    + ") اشتباه بود و ";
            message += this->new_game.moved_to_blucell(this->player_names[this->new_game.player_moved_to_bluecell_ID - 1]);
            QMessageBox::warning(this, "انتقال به خانه آبی", message, QMessageBox::Ok);
        }
    }
}


void RazeJangal::choice_message(int message_no){        // 1 : moved to bluecell 2: orange cell 3: both

    QString message1 =  "همه‌ی بازیکنان به جز " + this->player_names[this->new_game.get_current_player_ID() - 1] + " چشمانشان را ببندند!";
    QString message2;

    if(message_no > 1){
        if(this->choice == 1) {
        message2 = " گنج خونه‌ی " + QString::number(this->first_choice) + "، " + this->new_game.get_treasure_name(first_choice);
        }
        else if(this->choice == 2){
            message2 = " گنج خونه‌ی " + QString::number(this->second_choice) + "، " + this->new_game.get_treasure_name(this->second_choice);
        }
        message2 += " هستش \n";
    }

    if(message_no == 1){
        QMessageBox::warning(this,"انتقال به خانه آبی",
                             this->new_game.moved_to_blucell(this->player_names[this->new_game.player_moved_to_bluecell_ID - 1]),QMessageBox::Ok);
    }
    else if(message_no == 2){
        QMessageBox::warning(this, "اخظار", message1, QMessageBox::Ok);
        QMessageBox::information(this,"مشاهده گنج", message2, QMessageBox::Ok);
    }
    else if(message_no == 3){
        QMessageBox::warning(this,"انتقال به خانه آبی",
                             this->new_game.moved_to_blucell(this->player_names[this->new_game.player_moved_to_bluecell_ID - 1]),QMessageBox::Ok);
        QMessageBox::warning(this, "اخظار", message1, QMessageBox::Ok);
        QMessageBox::information(this,"مشاهده گنج", message2, QMessageBox::Ok);
    }
}

int Game::get_current_round(){
    return this->current_round;
}

std::pair<int, int> Game::this_players_rolls(){
    std::pair<int, int> dice;
    dice.first = this->current_player_first_roll;
    dice.second = this->current_player_second_roll;
    return dice;
}

void Game::set_players_name(string player_name, int player_number){
    this->new_board.get_players()[player_number].set_name(player_name);
}

int Game::get_treasure_num(int player_num){
    return this->new_board.get_players()[player_num].get_treasure_number();
}

void Game::set_players(int n) {
    this->number_of_players = n;
    this->new_board.set_players(n);
    this->current_player = &this->new_board.get_players()[0];
}

string Game::get_starting_message() {
    return "???¹?¯?§?¯ ?¨?§?²UŒ?©U†?§?±Uˆ Uˆ?§?±?¯ ?©U†\n";
}

void Game::new_round() {
        // sets this rounds treasure goal randomly from remained treasures
    int rnd = (rand() % this->remained_treasures.size());
    this->current_round++;
    this->current_treasure_goal = this->remained_treasures[rnd];
}

int Game::get_position(int player_num){
    return this->new_board.get_players()[player_num].get_current_cell()->get_ID();
}

void Game::get_new_turn_options() {

    vector<int> available_cells;

    std::vector<BoardCell*> available_cells1;
    std::vector<BoardCell*> available_cells2;

        // finds the neighbour cell that player can move there
    this->find_neighbours(&available_cells1,this->current_player->get_current_cell(),0,this->current_player_first_roll);     // with first dice
    this->find_neighbours(&available_cells2,this->current_player->get_current_cell(),0,this->current_player_second_roll);    // with second dice
    this->first_roll_options = available_cells1.size();

    if(this->current_player_first_roll != this->current_player_second_roll) {
        this->normal_available_cells.clear();
        this->normal_available_cells.reserve(available_cells1.size()+available_cells2.size());
        this->normal_available_cells.insert(this->normal_available_cells.end(),available_cells1.begin(),available_cells1.end());
        this->normal_available_cells.insert(this->normal_available_cells.end(),available_cells2.begin(),available_cells2.end());
        this->valid_choices_for_second_roll = this->normal_available_cells.size();
    }
    else{
        this->normal_available_cells.clear();
        this->bonus_available_cells.clear();
        this->normal_available_cells = available_cells1;

            // choices which player can have second choice after them
        this->valid_choices_for_second_roll = this->normal_available_cells.size();

//            // adds orange cell to options
        for(unsigned int i = 0; i <= this->new_board.get_orange_cells().size(); i++) {
            if(this->new_board.get_orange_cells()[i].get_current_player() == nullptr) {
                this->bonus_available_cells.push_back(&this->new_board.get_orange_cells()[i]);
            }
        }

//            // adds violet cell to options
        if(this->new_board.get_violet_cell().get_current_player() == nullptr) {
            this->bonus_available_cells.push_back(&this->new_board.get_violet_cell());
        }
    }
}

void Game::get_second_cell_options(int first_choice) {
    this->normal_available_cells.clear();
        // checks to see if player moved with the first dice or the second one and finds available cell with available moves
    if(this->moved_dice(first_choice) == 1){
        this->find_neighbours(&this->normal_available_cells,this->current_player->get_current_cell(),0,this->current_player_second_roll);
    }
    else if(this->moved_dice(first_choice) == 2) {
        this->find_neighbours(&this->normal_available_cells,this->current_player->get_current_cell(),0,this->current_player_first_roll);
    }
}

string Game::name_asking_message(){
    return "U†?§U… ?¨?§?²UŒ?©U†?§?±Uˆ Uˆ?§?±?¯ ?©U†:\n";
}

vector<BoardCell*> Game::get_normal_available_cells(){
    return this->normal_available_cells;
}

vector<BoardCell*> Game::get_bonus_available_cells(){
    return this->bonus_available_cells;
}


void Game::clear_normal_available_cells(){
    this->normal_available_cells.clear();
}

void Game::clear_bonus_available_cells(){
    this->bonus_available_cells.clear();
}

int Game::player_chose(unsigned int cell_ID, int type_of_choice) {
    int message = 0;        // 1 : moved to bluecell 2: orange cell 3: both
        // if player didn't choose to change the treasure
    if(cell_ID > 0) {
        BoardCell* cell = this->new_board.cells[cell_ID - 1];
        if(type_of_choice == 1){

                // if the cell wasn't empty move the previous player to the blue cells
            if(cell->get_current_player() != nullptr){
                message++;
                this->player_moved_to_bluecell_ID = cell->get_current_player()->get_ID();
                cell->get_current_player()->move(&(this->new_board.get_blue_cells()[cell->get_current_player()->get_ID() - 1]));
            }
            this->current_player->move(cell);
        }

        if(type_of_choice == 0 && cell->get_current_player() == nullptr){
            this->current_player->move(cell);
        }

        if(cell->get_color() == "Orange"){
            message += 2;
        }
    }
    return message;
}

int Game::get_current_player_ID(){
    return this->current_player->get_ID();
}

int Game::violet_cell_ID(){
    return this->new_board.get_violet_cell().get_ID();
}

QString Game::change_treasure_goal(){
    int rnd = rand() % this->remained_treasures.size();
    this->current_treasure_goal = this->remained_treasures[rnd];

    QString message = "گنج هدف این مرحله به ";
    message += this->remained_treasures[rnd]->get_name();
    message += " تغییر یافت\n";
    return message;
}

int Game::red_cell_ID(){
    return this->new_board.get_red_cell().get_ID();
}

std::vector<int> Game::orange_cell_ID(){
    vector<int> tmp;

    for(unsigned int i = 0; i < this->new_board.get_orange_cells().size(); i++){
        tmp.push_back(this->new_board.get_orange_cells()[i].get_ID());
    }

    return tmp;
}

Game::Game() {
        // preparing the game
    this->current_player = &this->new_board.get_players()[0];
    this->current_round = 0;
        // preparing the treasures
    this->remained_treasures.clear();
    this->current_treasure_goal = nullptr;
    for(int i = 0; i < 13; i++){
        this->remained_treasures.push_back(&(this->new_board.get_treasures()[i]));
    }
}

void Game::distribute_treasures() {
    int rnd;

    for(int i = 0; i < 13; i++){                    // putting treasures randomly in orange cells
        int k = 0;
        int j = 0;
        rnd = (rand() % (13 - i)) + 1;

        for(j = 0; k < rnd; j++){                      // finding the (rnd)'th not chosen orange cell => j
            if(this->new_board.get_orange_cells()[j].get_treasure() == nullptr){
                k++;
            }
        }

            // and putting the ith treasure in jth orange cell
        this->new_board.get_orange_cells()[j-1].set_treasure(&this->new_board.get_treasures()[i]);
        this->new_board.get_treasures()[i].cell = &this->new_board.get_orange_cells()[j-1];
    }
}

int Game::get_red_cell_message(int player_choice) { // returns 1 : player guessed and was right , 2 : player guessed and was wrong , 0 : player didn't guess
    int message = 0;
    if(player_choice > 0) {             // if player wanted to guess

            // the cell that player think that contains the treasure
        BoardCell* cell = this->new_board.cells[player_choice - 1];

            // if players guess was correct
        if (cell->get_treasure()->get_name() == this->current_treasure_goal->get_name()){
            message = 1;
                // adds the found treasure to player's achievements
            this->current_player->add_trasure(this->current_treasure_goal);

                // removes the found treasure from the list of remained treasures
            for(auto it = this->remained_treasures.begin(); it < this->remained_treasures.end(); it++){
                if(this->current_treasure_goal == *it){
                    this->remained_treasures.erase(it);
                }
            }

        }
        else{       // if player's guess was not correct
            message = 2;
            this->player_moved_to_bluecell_ID = this->current_player->get_ID();
            this->current_player->move(&this->new_board.get_blue_cells()[this->current_player->get_ID() - 1]);
        }
    }

    return message;
}

QString Game::moved_to_blucell(QString player_name) {
    QString message = "متاسفانه " + player_name + " بدلیل مجروحیت و برای درمان به خونه های ابی منتقل شد\n";
    return message;
}

BoardCell *Game::find_neighbours(vector<BoardCell*>* available_cells, BoardCell *current_cell, int previous_cell_ID, int length) {

    // finds neighbours in (length) cells
    if(length == 0) {
        (*available_cells).resize((*available_cells).size()+1);
        (*available_cells)[(*available_cells).size()-1] = current_cell;
    } else{
        for (unsigned int i = 0; i < current_cell->get_neighbours().size(); i++) {
            int ID = current_cell->get_neighbours()[i]->get_ID();
            if(ID > 0 && ID != previous_cell_ID)
                this->find_neighbours(available_cells,current_cell->get_neighbours()[i], current_cell->get_ID(), length - 1);
        }
    }
    return nullptr;
}

bool Game::player_moved_to_red() {
    return this->current_player->get_current_cell()->get_color() == "Red";
}

std::string Game::get_red_cell_options() {
    // generates message for options of the player in the red cell
    string message = "";
    message = this->current_player->get_name() + " در " +
            this->current_player->get_current_cell()->get_info() +
            + "هستش و میتونه تلاش کنه مکان گنج هدف این مرحله رو حدس بزنه\n" +
            "1. نمیخوام حدس بزنم\n";

    for(unsigned int i = 0; i < this->new_board.get_orange_cells().size(); i++) {
        message += to_string(i+2)+ ". اون توی  " + to_string(this->new_board.get_orange_cells()[i].get_ID()) + "هستش";
        message += "\n";
    }
    return message;
}

void Board::set_players(int number_of_players) {    // prepares the players
    this->players.resize(number_of_players);
    for(int i = 1; i <= number_of_players; i++){
        this->players[i-1].move(&this->blue_cells[i-1]);
        this->players[i-1].set_ID(i);
        this->blue_cells[i-1].set_current_player(&this->players[i-1]);
    }
}

vector<Player>& Board::get_players() {
    return this->players;
}

int Board::roll_dice() {
    return this->dice.random_roll();
//    return this->dice.roll_from_file();
}

std::vector<OrangeCell>& Board::get_orange_cells() {
    return this->orange_cells;
}

VioletCell& Board::get_violet_cell() {
    return this->violet_cell;
}

RedCell& Board::get_red_cell() {
    return this->red_cell;
}

std::vector<BlueCell> &Board::get_blue_cells() {
    return this->blue_cells;
}

Board::Board() {
        // generating the treasures
    for(int i = 0; i < 13; i++){
        this->treasures.resize(13);
        this->treasures[i].set_name(static_cast<char>(65 + i));
    }

        // generating the map
    this->blue_cells.resize(4);
    int orange_ID[13], counter = 0, number_of_greencells = 0, redcell_id, violetcell_id;
    for (int j = 0; j < 4; ++j) {
        this->blue_cells[j].set_ID(-j-1);
    }
    fstream myfile1 (this->address + "newpositions.txt");
    if (myfile1.is_open())
    {
        int number, X, Y, aux = 0;
        string color;

        while (myfile1 >> number) {
            myfile1 >> X >> Y >> color;
            if(color == "red"){
                this->red_cell.set_ID(number);
                redcell_id = number;
            }
            if(color == "orange"){
                orange_ID[counter] = number;
                counter ++;
            }

            if(color == "violet"){
                violetcell_id = number;
                this->violet_cell.set_ID(number);
            }

            if(color == "green"){
                number_of_greencells++;

            }
        }
        myfile1.close();

    }
    else cout << "Unable to open file";

    this->orange_cells.resize(13);

    for (int j = 0; j < 13; ++j) {
        this->orange_cells[j].set_ID(orange_ID[j]);
    }





    this->green_cells.resize(number_of_greencells);

    int l = 0;
    int j = 0;

    for (int k = 1; k <= number_of_greencells + 15; ++k) {
        if(k == violetcell_id){
            this->cells.push_back(&violet_cell);
        } else if(k == redcell_id){
            this->cells.push_back(&red_cell);
        } else if(k == orange_ID[l]) {
            this->cells.push_back(&this->orange_cells[l]);
            if (l < 13) {
                l++;
            }
        } else {
            this->green_cells[j].set_ID(k);
            this->cells.push_back(&this->green_cells[j]);
            j++;
        }
    }

        // setting neighbours
    this->set_neighbours(&this->blue_cells[0],this->cells[0]);      // setting neighbour of the blue cells
    this->set_neighbours(&this->blue_cells[1],this->cells[0]);
    this->set_neighbours(&this->blue_cells[2],this->cells[0]);
    this->set_neighbours(&this->blue_cells[3],this->cells[0]);

        // setting other neighbours from the file
    int ID1;
    int ID2;
    ifstream myfile (this->address + "neighbours.txt");
    if (myfile.is_open())
    {
        while (myfile >> ID1)
        {
            myfile >> ID2;
            this->set_neighbours(this->cells[ID1],this->cells[ID2]);
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

std::vector<Treasure> &Board::get_treasures() {
    return this->treasures;
}

void Board::set_neighbours(BoardCell *first_cell, BoardCell *second_cell) {
    first_cell->add_neighbour(second_cell);
    second_cell->add_neighbour(first_cell);
}

void Player::set_ID(int ID) {
    this->ID = ID;
}
void Player::set_name(string name){
    this->name = name;
}
string Player::get_name(){
    return this->name;
}

int Player::get_treasure_number(){
    return this->achieved_treasures.size();
}

int Player::get_ID() {
    return this->ID;
}

void Player::add_trasure(Treasure* treasure) {
    this->achieved_treasures.push_back(treasure);
}
void Player::move(BoardCell *cell) {
    if(this->get_current_cell() != nullptr)
        this->get_current_cell()->set_current_player(nullptr);
    this->current_cell = cell;
    cell->set_current_player(this);
}

BoardCell *Player::get_current_cell() {
    return this->current_cell;
}

std::string BoardCell::get_color() {
    return "";
}

Treasure* BoardCell::get_treasure() {
    return nullptr;
}

Player *BoardCell::get_current_player() {
    return this->current_player;
}

void BoardCell::set_current_player(Player *player) {
    this->current_player = player;
}

int BoardCell::get_ID() {
    return this->ID;
}

void BoardCell::set_ID(int ID) {
    this->ID = ID;
}

std::vector<BoardCell *> BoardCell::get_neighbours() {
    return this->neighbours;
}

std::string BoardCell::get_info() {
    string text = to_string(this->ID);
    string color =  this->get_color();
    if(color != "Green")
        text += "(" + color + ")";
    return text;
}

BoardCell::BoardCell() {
    this->current_player = nullptr;
}

void BoardCell::add_neighbour(BoardCell *cell) {
    this->neighbours.push_back(cell);
}

std::string GreenCell::get_color() {
    return "Green";
}

std::string BlueCell::get_color() {
    return "Blue";
}

std::string RedCell::get_color() {
    return "Red";
}

std::string VioletCell::get_color() {
    return "Violet";
}

std::string OrangeCell::get_color() {
    return "Orange";
}

void OrangeCell::set_treasure(Treasure* treasure) {
    this->treasure = treasure;
}

Treasure* OrangeCell::get_treasure() {
    return this->treasure;
}

OrangeCell::OrangeCell() {
    this->treasure = nullptr;
}

void Treasure::set_name(char name) {
    this->name = name;
}

char Treasure::get_name() {
    return this->name;
}

void RazeJangal::on_Change_treasure_clicked()
{
    QString message = this->new_game.change_treasure_goal();

    QString treasure_info = "گنج این مرحله: ";
    treasure_info += this->new_game.get_current_treasure();
    ui->Treasure_Info->setText(treasure_info);
    ui->Treasure_Info->setStyleSheet("font-size: 14pt");

    QMessageBox::information(this,"تغییر گنج", message, QMessageBox::Ok);

    ui->Change_treasure->setVisible(false);
    this->first_choice = 0;
    this->new_game.clear_normal_available_cells();
    this->new_game.clear_bonus_available_cells();
    this->set_map();
    this->normal_wait.exit();
    this->type_of_choice = 0;
}

void RazeJangal::on_Cell_1_clicked()
{
    this->set_choice(1);
    this->set_redcell_choice(1);
}

void RazeJangal::on_Cell_2_clicked()
{
    this->set_choice(2);
    this->set_redcell_choice(2);
}

void RazeJangal::on_Cell_3_clicked()
{
    this->set_choice(3);
    this->set_redcell_choice(3);
}

void RazeJangal::on_Cell_4_clicked()
{
    this->set_choice(4);
    this->set_redcell_choice(4);
}

void RazeJangal::on_Cell_5_clicked()
{
    this->set_choice(5);
    this->set_redcell_choice(5);
}

void RazeJangal::on_Cell_6_clicked()
{
    this->set_choice(6);
    this->set_redcell_choice(6);
}

void RazeJangal::on_Cell_7_clicked()
{
    this->set_choice(7);
    this->set_redcell_choice(7);
}

void RazeJangal::on_Cell_8_clicked()
{
    this->set_choice(8);
    this->set_redcell_choice(8);
}

void RazeJangal::on_Cell_9_clicked()
{
    this->set_choice(9);
    this->set_redcell_choice(9);
}

void RazeJangal::on_Cell_10_clicked()
{
    this->set_choice(10);
    this->set_redcell_choice(10);
}

void RazeJangal::on_Cell_11_clicked()
{
    this->set_choice(11);
    this->set_redcell_choice(11);
}

void RazeJangal::on_Cell_12_clicked()
{
    this->set_choice(12);
    this->set_redcell_choice(12);
}

void RazeJangal::on_Cell_13_clicked()
{
    this->set_choice(13);
    this->set_redcell_choice(13);
}

void RazeJangal::on_Cell_14_clicked()
{
    this->set_choice(14);
    this->set_redcell_choice(14);
}

void RazeJangal::on_Cell_15_clicked()
{
    this->set_choice(15);
    this->set_redcell_choice(15);
}

void RazeJangal::on_Cell_16_clicked()
{
    this->set_choice(16);
    this->set_redcell_choice(16);
}

void RazeJangal::on_Cell_17_clicked()
{
    this->set_choice(17);
    this->set_redcell_choice(17);
}

void RazeJangal::on_Cell_18_clicked()
{
    this->set_choice(18);
    this->set_redcell_choice(18);
}

void RazeJangal::on_Cell_19_clicked()
{
    this->set_choice(19);
    this->set_redcell_choice(19);
}

void RazeJangal::on_Cell_20_clicked()
{
    this->set_choice(20);
    this->set_redcell_choice(20);
}

void RazeJangal::on_Cell_21_clicked()
{
    this->set_choice(21);
    this->set_redcell_choice(21);
}

void RazeJangal::on_Cell_22_clicked()
{
    this->set_choice(22);
    this->set_redcell_choice(22);
}

void RazeJangal::on_Cell_23_clicked()
{
    this->set_choice(23);
    this->set_redcell_choice(23);
}

void RazeJangal::on_Cell_24_clicked()
{
    this->set_choice(24);
    this->set_redcell_choice(24);
}

void RazeJangal::on_Cell_25_clicked()
{
    this->set_choice(25);
    this->set_redcell_choice(25);
}

void RazeJangal::on_Cell_26_clicked()
{
    this->set_choice(26);
    this->set_redcell_choice(26);
}

void RazeJangal::on_Cell_27_clicked()
{
    this->set_choice(27);
    this->set_redcell_choice(27);
}

void RazeJangal::on_Cell_28_clicked()
{
    this->set_choice(28);
    this->set_redcell_choice(28);
}

void RazeJangal::on_Cell_29_clicked()
{
    this->set_choice(29);
    this->set_redcell_choice(29);
}

void RazeJangal::on_Cell_30_clicked()
{
    this->set_choice(30);
    this->set_redcell_choice(30);
}

void RazeJangal::on_Cell_31_clicked()
{
    this->set_choice(31);
    this->set_redcell_choice(31);
}

void RazeJangal::on_Cell_32_clicked()
{
    this->set_choice(32);
    this->set_redcell_choice(32);
}

void RazeJangal::on_Cell_33_clicked()
{
    this->set_choice(33);
    this->set_redcell_choice(33);
}

void RazeJangal::on_Cell_34_clicked()
{
    this->set_choice(34);
    this->set_redcell_choice(34);
}

void RazeJangal::on_Cell_35_clicked()
{
    this->set_choice(35);
    this->set_redcell_choice(35);
}

void RazeJangal::on_Cell_36_clicked()
{
    this->set_choice(36);
    this->set_redcell_choice(36);
}

void RazeJangal::on_Cell_37_clicked()
{
    this->set_choice(37);
    this->set_redcell_choice(37);
}

void RazeJangal::on_Cell_38_clicked()
{
    this->set_choice(38);
    this->set_redcell_choice(38);
}

void RazeJangal::on_Cell_39_clicked()
{
    this->set_choice(39);
    this->set_redcell_choice(39);
}

void RazeJangal::on_Cell_40_clicked()
{
    this->set_choice(40);
    this->set_redcell_choice(40);
}

void RazeJangal::on_Cell_41_clicked()
{
    this->set_choice(41);
    this->set_redcell_choice(41);
}

void RazeJangal::on_Cell_42_clicked()
{
    this->set_choice(42);
    this->set_redcell_choice(42);
}

void RazeJangal::on_Cell_43_clicked()
{
    this->set_choice(43);
    this->set_redcell_choice(43);
}

void RazeJangal::on_Cell_44_clicked()
{
    this->set_choice(44);
    this->set_redcell_choice(44);
}

void RazeJangal::on_Cell_45_clicked()
{
    this->set_choice(45);
    this->set_redcell_choice(45);
}

void RazeJangal::on_Cell_46_clicked()
{
    this->set_choice(46);
    this->set_redcell_choice(46);
}

void RazeJangal::on_Cell_47_clicked()
{
    this->set_choice(47);
    this->set_redcell_choice(47);
}

void RazeJangal::on_Cell_48_clicked()
{
    this->set_choice(48);
    this->set_redcell_choice(48);
}

void RazeJangal::on_Cell_49_clicked()
{
    this->set_choice(49);
    this->set_redcell_choice(49);
}

void RazeJangal::on_Cell_50_clicked()
{
    this->set_choice(50);
    this->set_redcell_choice(50);
}

void RazeJangal::on_Cell_51_clicked()
{
    this->set_choice(51);
    this->set_redcell_choice(51);
}

void RazeJangal::on_Cell_52_clicked()
{
    this->set_choice(52);
    this->set_redcell_choice(52);
}

void RazeJangal::on_Cell_53_clicked()
{
    this->set_choice(53);
    this->set_redcell_choice(53);
}

void RazeJangal::on_Cell_54_clicked()
{
    this->set_choice(54);
    this->set_redcell_choice(54);
}

void RazeJangal::on_Cell_55_clicked()
{
    this->set_choice(55);
    this->set_redcell_choice(55);
}

void RazeJangal::on_Cell_56_clicked()
{
    this->set_choice(56);
    this->set_redcell_choice(56);
}

void RazeJangal::on_Cell_57_clicked()
{
    this->set_choice(57);
    this->set_redcell_choice(57);
}

void RazeJangal::on_Cell_58_clicked()
{
    this->set_choice(58);
    this->set_redcell_choice(58);
}

void RazeJangal::on_Cell_59_clicked()
{
    this->set_choice(59);
    this->set_redcell_choice(59);
}

void RazeJangal::on_Cell_60_clicked()
{
    this->set_choice(60);
    this->set_redcell_choice(60);
}

void RazeJangal::on_Cell_61_clicked()
{
    this->set_choice(61);
    this->set_redcell_choice(61);
}

void RazeJangal::on_Cell_62_clicked()
{
    this->set_choice(62);
    this->set_redcell_choice(62);
}

void RazeJangal::on_Cell_63_clicked()
{
    this->set_choice(63);
    this->set_redcell_choice(63);
}

void RazeJangal::on_Cell_64_clicked()
{
    this->set_choice(64);
    this->set_redcell_choice(64);
}

void RazeJangal::on_Cell_65_clicked()
{
    this->set_choice(65);
    this->set_redcell_choice(65);
}

void RazeJangal::on_Cell_66_clicked()
{
    this->set_choice(66);
    this->set_redcell_choice(66);
}

void RazeJangal::on_Cell_67_clicked()
{
    this->set_choice(67);
    this->set_redcell_choice(67);
}

void RazeJangal::on_Cell_68_clicked()
{
    this->set_choice(68);
    this->set_redcell_choice(68);
}

void RazeJangal::on_Cell_69_clicked()
{
    this->set_choice(69);
    this->set_redcell_choice(69);
}

void RazeJangal::on_Cell_70_clicked()
{
    this->set_choice(70);
    this->set_redcell_choice(70);
}

void RazeJangal::on_Cell_71_clicked()
{
    this->set_choice(71);
    this->set_redcell_choice(71);
}

void RazeJangal::on_Cell_72_clicked()
{
    this->set_choice(72);
    this->set_redcell_choice(72);
}

void RazeJangal::on_Cell_73_clicked()
{
    this->set_choice(73);
    this->set_redcell_choice(73);
}

void RazeJangal::on_Cell_74_clicked()
{
    this->set_choice(74);
    this->set_redcell_choice(74);
}

void RazeJangal::on_Cell_75_clicked()
{
    this->set_choice(75);
    this->set_redcell_choice(75);
}

void RazeJangal::on_Cell_76_clicked()
{
    this->set_choice(76);
    this->set_redcell_choice(76);
}

void RazeJangal::on_Cell_77_clicked()
{
    this->set_choice(77);
    this->set_redcell_choice(77);
}

void RazeJangal::on_Cell_78_clicked()
{
    this->set_choice(78);
    this->set_redcell_choice(78);
}

void RazeJangal::on_Cell_79_clicked()
{
    this->set_choice(79);
    this->set_redcell_choice(79);
}

void RazeJangal::on_Cell_80_clicked()
{
    this->set_choice(80);
    this->set_redcell_choice(80);
}

void RazeJangal::on_Cell_81_clicked()
{
    this->set_choice(81);
    this->set_redcell_choice(81);
}

void RazeJangal::on_Cell_82_clicked()
{
    this->set_choice(82);
    this->set_redcell_choice(82);
}

void RazeJangal::on_Cell_83_clicked()
{
    this->set_choice(83);
    this->set_redcell_choice(83);
}

void RazeJangal::on_Cell_84_clicked()
{
    this->set_choice(84);
    this->set_redcell_choice(84);
}

void RazeJangal::on_Cell_85_clicked()
{
    this->set_choice(85);
    this->set_redcell_choice(85);
}

void RazeJangal::on_Cell_86_clicked()
{
    this->set_choice(86);
    this->set_redcell_choice(86);
}

void RazeJangal::on_Cell_87_clicked()
{
    this->set_choice(87);
    this->set_redcell_choice(87);
}

void RazeJangal::on_Cell_88_clicked()
{
    this->set_choice(88);
    this->set_redcell_choice(88);
}

void RazeJangal::on_Cell_89_clicked()
{
    this->set_choice(89);
    this->set_redcell_choice(89);
}

void RazeJangal::on_Cell_90_clicked()
{
    this->set_choice(90);
    this->set_redcell_choice(90);
}

void RazeJangal::on_Cell_91_clicked()
{
    this->set_choice(91);
    this->set_redcell_choice(91);
}

void RazeJangal::on_Cell_92_clicked()
{
    this->set_choice(92);
    this->set_redcell_choice(92);
}

void RazeJangal::on_Cell_93_clicked()
{
    this->set_choice(93);
    this->set_redcell_choice(93);
}

void RazeJangal::on_Cell_94_clicked()
{
    this->set_choice(94);
    this->set_redcell_choice(94);
}

void RazeJangal::on_Cell_95_clicked()
{
    this->set_choice(95);
    this->set_redcell_choice(95);
}

void RazeJangal::on_Cell_96_clicked()
{
    this->set_choice(96);
    this->set_redcell_choice(96);
}

void RazeJangal::on_Cell_97_clicked()
{
    this->set_choice(97);
    this->set_redcell_choice(97);
}

void RazeJangal::on_Cell_98_clicked()
{
    this->set_choice(98);
    this->set_redcell_choice(98);
}

void RazeJangal::on_Cell_99_clicked()
{
    this->set_choice(99);
    this->set_redcell_choice(99);
}

void RazeJangal::on_Cell_100_clicked()
{
    this->set_choice(100);
    this->set_redcell_choice(100);
}

void RazeJangal::on_Cell_101_clicked()
{
    this->set_choice(101);
    this->set_redcell_choice(101);
}

void RazeJangal::on_Cell_102_clicked()
{
    this->set_choice(102);
    this->set_redcell_choice(102);
}

void RazeJangal::on_Cell_103_clicked()
{
    this->set_choice(103);
    this->set_redcell_choice(103);
}

void RazeJangal::on_Cell_104_clicked()
{
    this->set_choice(104);
    this->set_redcell_choice(104);
}

void RazeJangal::on_Cell_105_clicked()
{
    this->set_choice(105);
    this->set_redcell_choice(105);
}

void RazeJangal::on_Cell_106_clicked()
{
    this->set_choice(106);
    this->set_redcell_choice(106);
}

void RazeJangal::on_Cell_107_clicked()
{
    this->set_choice(107);
    this->set_redcell_choice(107);
}

void RazeJangal::on_Cell_108_clicked()
{
    this->set_choice(108);
    this->set_redcell_choice(108);
}

void RazeJangal::on_Cell_109_clicked()
{
    this->set_choice(109);
    this->set_redcell_choice(109);
}

void RazeJangal::on_Cell_110_clicked()
{
    this->set_choice(110);
    this->set_redcell_choice(110);
}

void RazeJangal::on_Cell_111_clicked()
{
    this->set_choice(111);
    this->set_redcell_choice(111);
}

void RazeJangal::on_Cell_112_clicked()
{
    this->set_choice(112);
    this->set_redcell_choice(112);
}

void RazeJangal::on_Cell_113_clicked()
{
    this->set_choice(113);
    this->set_redcell_choice(113);
}

void RazeJangal::on_Cell_114_clicked()
{
    this->set_choice(114);
    this->set_redcell_choice(114);
}

void RazeJangal::on_Cell_115_clicked()
{
    this->set_choice(115);
    this->set_redcell_choice(115);
}

void RazeJangal::on_Cell_116_clicked()
{
    this->set_choice(116);
    this->set_redcell_choice(116);
}

void Game::change_player(int change_player){
    if(change_player)
        this->current_player = &this->new_board.get_players()[this->current_player->get_ID() %
                                this->new_board.get_players().size()];
}

QString Game::get_current_treasure(){
    QString treasure = "";
    treasure = this->current_treasure_goal->get_name();
    return treasure;
}

int Game::type_of_choice(int cell_ID){      // 1 : normal , 0 : bonus , -1 : non valid
    for(int i = 0; i < this->normal_available_cells.size(); i++){
        if(cell_ID == this->normal_available_cells[i]->get_ID()){
            return 1;
        }
    }

    for(int i = 0; i < this->bonus_available_cells.size(); i++){
        if(cell_ID == this->bonus_available_cells[i]->get_ID()){
            return 0;
        }
    }

    return -1;

}

int Game::roll_dice(){
    return this->new_board.roll_dice();
}

void Game::set_current_player_rolls(int first_roll, int second_roll){
    this->current_player_first_roll = first_roll;
    this->current_player_second_roll = second_roll;
}

QString Game::get_treasure_name(int cell_ID){
    string text = "";
    text += this->new_board.cells[cell_ID - 1]->get_treasure()->get_name();
    return QString::fromStdString(text);
}

int Game::moved_dice(int chosen_cell_ID){
    if(chosen_cell_ID == 0)
        return 0;
    else{

        for(int i = 0; i < this->first_roll_options; i++){
            if(this->normal_available_cells[i]->get_ID() == chosen_cell_ID){
                return 1;
            }
        }

    }
    return 2;
}

void RazeJangal::on_Dont_guess_clicked()
{
    if(this->choice == 2){
        this->dont_guess = true;
    }
    this->redcell_choice = -1;
    this->set_map();
    ui->Dont_guess->setVisible(false);
    redcell_wait.exit();
}

void RazeJangal::on_Exit_clicked()
{
    this->close();
}

void RazeJangal::on_pushButton_3_clicked()
{

}

void RazeJangal::on_pushButton_2_clicked()
{

}

void RazeJangal::on_pushButton_clicked()
{

}
