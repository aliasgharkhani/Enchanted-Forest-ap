#ifndef RAZEJANGAL_H
#define RAZEJANGAL_H

#include <qlabel.h>
#include <qpushbutton.h>
#include <QMainWindow>
#include <QEventLoop>
#include <iostream>
#include <vector>
#include <string>
#include <map>

class Game;
class Board;
class Player;
class Treasure;
class DicePool;
class BoardCell;

class DicePool{
    std::vector<int> numbers;
public:
    std::string address = "";
    DicePool();
    int random_roll();
    int roll_from_file();
};

class Player{
private:
    int ID;
    std::string name;
    std::vector<Treasure*> achieved_treasures;
    BoardCell* current_cell = nullptr;
public:
    int get_ID();
    void set_name(std::string name);
    std::string get_name();
    int get_treasure_number();
    void set_ID(int ID);
    void move(BoardCell* cell);
    BoardCell* get_current_cell();
    void add_trasure(Treasure* treasure);
};

class BoardCell{
private:
    int ID;
    Player* current_player;
    std::vector<BoardCell*> neighbours;
public:
    BoardCell();
    int get_ID();
    void set_ID(int ID);
    std::string get_info();
    virtual Treasure* get_treasure();
    Player* get_current_player();
    virtual std::string get_color();
    void set_current_player(Player* player);
    std::vector<BoardCell*> get_neighbours();
    void add_neighbour(BoardCell* cell);
};

class GreenCell : public BoardCell{
public:
    virtual std::string get_color();
};

class BlueCell : public BoardCell{
public:
    virtual std::string get_color();
};

class RedCell : public  BoardCell{
public:
    virtual std::string get_color();
};

class VioletCell : public BoardCell{
public:
    virtual std::string get_color();
};

class OrangeCell : public BoardCell{
private:
    Treasure* treasure;

public:
    OrangeCell();
    virtual Treasure* get_treasure();
    virtual std::string get_color();
    virtual void set_treasure(Treasure* treasure);
};

class Board{
private:
    std::string address = "";
    DicePool dice;
    RedCell red_cell;
    VioletCell violet_cell;
    std::vector<Player> players;
    std::vector<Treasure> treasures;
    std::vector<BlueCell> blue_cells;
    std::vector<GreenCell> green_cells;
    std::vector<OrangeCell> orange_cells;
public:
    Board();
    int roll_dice();
    VioletCell& get_violet_cell();
    RedCell& get_red_cell();
    std::vector<BoardCell*> cells;
    std::vector<Player>& get_players();
    std::vector<Treasure>& get_treasures();
    std::vector<BlueCell>& get_blue_cells();
    void set_players(int number_of_players);
    std::vector<OrangeCell>& get_orange_cells();
    void set_neighbours(BoardCell* first_cell, BoardCell* second_cell);
};

class Treasure{
    char name;
public:
    BoardCell* cell = nullptr;
    void set_name(char name);
    char get_name();
};


class Game{
private:
    int current_player_first_roll;
    int current_player_second_roll;
    int first_roll_options;
    Board new_board;
    int current_round;
    int number_of_players;
    Player* current_player;
    Treasure* current_treasure_goal;
    std::vector<BoardCell*> normal_available_cells;
    std::vector<BoardCell*> bonus_available_cells;
    std::vector<Treasure*> remained_treasures;
    BoardCell* find_neighbours(std::vector<BoardCell*>* available_cells, BoardCell* current_cell, int previous_cell_ID, int length);

public:
    QString get_current_treasure();
    void change_player(int change_player);
    int type_of_choice(int cell_ID); // 1 : normal , 0 : bonus , -1 : non valid
    int player_moved_to_bluecell_ID;
    Game();
    int roll_dice();
    void set_current_player_rolls(int first_roll, int second_roll);
    QString get_treasure_name(int cell_ID);
    int moved_dice(int chosen_cell_ID);
    QString change_treasure_goal();
    int red_cell_ID();
    int violet_cell_ID();
    std::vector<int> orange_cell_ID();
    int get_current_player_ID();
    int get_current_round();
    std::pair<int, int> this_players_rolls();
    std::vector<BoardCell*> get_normal_available_cells();
    std::vector<BoardCell*> get_bonus_available_cells();
    void clear_normal_available_cells();
    void clear_bonus_available_cells();
    int get_treasure_num(int player_num);
    void set_players(int n);
    bool player_moved_to_red();
    void distribute_treasures();
    int valid_choices_for_second_roll;
    int get_position(int player_num);
    void set_players_name(std::string player_name, int player_number);
    std::string get_starting_message();
    std::string name_asking_message();
    std::string get_red_cell_options();
    void new_round();
    int player_chose(unsigned int player_choice, int type_of_choice);        //after player chose the next cell, sets player's choice and gets the proper message
    QString moved_to_blucell(QString player_name);
    int get_red_cell_message(int player_choice);
    void get_new_turn_options();
    void get_second_cell_options(int first_choice);
};

///////
///
///////

namespace Ui {
class RazeJangal;
}

class RazeJangal : public QMainWindow
{
    Q_OBJECT

public:
    explicit RazeJangal(QWidget *parent = 0);
    ~RazeJangal();
    Game new_game;
    void start_game();
    QString get_current_treasure();
    void redcell_choice_message(int redcell_message_no);
    void choice_message(int message_no);
    void second_cell_options(int first_choice);
    void new_turn(int change_player);
    std::vector<QPushButton*> cells;
    std::vector<QPushButton*> blue_cells;
    std::vector<QLabel*> first_rolls;
    std::vector<QLabel*> second_rolls;
    std::vector<QLabel*> player_info;
    void set_choice(int cell_ID);
    void set_redcell_choice(int cell_ID);
    int first_choice;
    int second_choice;
    int redcell_choice;
    int number_of_players;
    std::vector<QString> player_names;
    void set_vectors();
    void set_map();
    void set_round();
    void redcell_options();
private:
    std::string address = "";
    bool dont_guess = false;
    int type_of_choice;
    int choice;         // first choice : 1 ; second choice : 2
    Ui::RazeJangal *ui;
    QEventLoop normal_wait;
    QEventLoop redcell_wait;
    QEventLoop editor_wait;
//    QEventLoop mapeditor;

private slots:
    void on_Change_treasure_clicked();
    void on_Cell_1_clicked();
    void on_Cell_2_clicked();
    void on_Cell_3_clicked();
    void on_Cell_4_clicked();
    void on_Cell_5_clicked();
    void on_Cell_6_clicked();
    void on_Cell_7_clicked();
    void on_Cell_8_clicked();
    void on_Cell_9_clicked();
    void on_Cell_10_clicked();
    void on_Cell_11_clicked();
    void on_Cell_12_clicked();
    void on_Cell_13_clicked();
    void on_Cell_14_clicked();
    void on_Cell_15_clicked();
    void on_Cell_16_clicked();
    void on_Cell_17_clicked();
    void on_Cell_18_clicked();
    void on_Cell_19_clicked();
    void on_Cell_20_clicked();
    void on_Cell_21_clicked();
    void on_Cell_22_clicked();
    void on_Cell_23_clicked();
    void on_Cell_24_clicked();
    void on_Cell_25_clicked();
    void on_Cell_26_clicked();
    void on_Cell_27_clicked();
    void on_Cell_28_clicked();
    void on_Cell_29_clicked();
    void on_Cell_30_clicked();
    void on_Cell_31_clicked();
    void on_Cell_32_clicked();
    void on_Cell_33_clicked();
    void on_Cell_34_clicked();
    void on_Cell_35_clicked();
    void on_Cell_36_clicked();
    void on_Cell_37_clicked();
    void on_Cell_38_clicked();
    void on_Cell_39_clicked();
    void on_Cell_40_clicked();
    void on_Cell_41_clicked();
    void on_Cell_42_clicked();
    void on_Cell_43_clicked();
    void on_Cell_44_clicked();
    void on_Cell_45_clicked();
    void on_Cell_46_clicked();
    void on_Cell_47_clicked();
    void on_Cell_48_clicked();
    void on_Cell_49_clicked();
    void on_Cell_50_clicked();
    void on_Cell_51_clicked();
    void on_Cell_52_clicked();
    void on_Cell_53_clicked();
    void on_Cell_54_clicked();
    void on_Cell_55_clicked();
    void on_Cell_56_clicked();
    void on_Cell_57_clicked();
    void on_Cell_58_clicked();
    void on_Cell_59_clicked();
    void on_Cell_60_clicked();
    void on_Cell_61_clicked();
    void on_Cell_62_clicked();
    void on_Cell_63_clicked();
    void on_Cell_64_clicked();
    void on_Cell_65_clicked();
    void on_Cell_66_clicked();
    void on_Cell_67_clicked();
    void on_Cell_68_clicked();
    void on_Cell_69_clicked();
    void on_Cell_70_clicked();
    void on_Cell_71_clicked();
    void on_Cell_72_clicked();
    void on_Cell_73_clicked();
    void on_Cell_74_clicked();
    void on_Cell_75_clicked();
    void on_Cell_76_clicked();
    void on_Cell_77_clicked();
    void on_Cell_78_clicked();
    void on_Cell_79_clicked();
    void on_Cell_80_clicked();
    void on_Cell_81_clicked();
    void on_Cell_82_clicked();
    void on_Cell_83_clicked();
    void on_Cell_84_clicked();
    void on_Cell_85_clicked();
    void on_Cell_86_clicked();
    void on_Cell_87_clicked();
    void on_Cell_88_clicked();
    void on_Cell_89_clicked();
    void on_Cell_90_clicked();
    void on_Cell_91_clicked();
    void on_Cell_92_clicked();
    void on_Cell_93_clicked();
    void on_Cell_94_clicked();
    void on_Cell_95_clicked();
    void on_Cell_96_clicked();
    void on_Cell_97_clicked();
    void on_Cell_98_clicked();
    void on_Cell_99_clicked();
    void on_Cell_100_clicked();
    void on_Cell_101_clicked();
    void on_Cell_102_clicked();
    void on_Cell_103_clicked();
    void on_Cell_104_clicked();
    void on_Cell_105_clicked();
    void on_Cell_106_clicked();
    void on_Cell_107_clicked();
    void on_Cell_108_clicked();
    void on_Cell_109_clicked();
    void on_Cell_110_clicked();
    void on_Cell_111_clicked();
    void on_Cell_112_clicked();
    void on_Cell_113_clicked();
    void on_Cell_114_clicked();
    void on_Cell_115_clicked();
    void on_Cell_116_clicked();
    void on_Dont_guess_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_Exit_clicked();
};

#endif // RAZEJANGAL_H
