#include <iostream>
#include<stdio.h>
#include <string>
#include <time.h>
#include <ctime>
#include <cstring>
using namespace std;
int row , column , bombs_num , moves_done=0 , flags_bomb=0 , all_flags=0, action , move_x , move_y , difficulty , discovered = 0;
string save_slot , autosave_status="OFF" , autosave_slot;
char username[100] , password[100] , userpass_data[202];
string s_username , s_password , s_userpass_data;
FILE *userfile;
char realboard[100][100] , fakeboard[100][100];

void difficulty2 ();
void bombplacer ();
void show_fakeboard ();
void show_realboard ();
void numbers_realboard ();
void if_0(int z2=0 ,int z=0);
void discover_move();
void flag_move();
void remove_flag();
void loadgame();
void play_loadgame();
void save_game(string save_slot);
void select_action();
void play_newgame();
void first_menu();
void main_menu();

int main()
{
    first_menu();
    return 0;
}

void difficulty2 ()
{
    switch (difficulty)
    {
        case -1:
        {
            main_menu();
            break;
        }
        case 1:
        {  
            row = 9;
            column = 9;
            bombs_num = 10;
            break;
        }
        case 2:
        {
            row = 16;
            column = 16;
            bombs_num = 40;
            break;
        }
        case 3:
        {
            row = 16;
            column = 30;
            bombs_num = 99;
            break;
        }
        case 4:
        {
            cout << "Please enter Row number: ";
            cin >> row;
            cout << "Please enter column number: ";
            cin >> column;
            cout << "Please enter Bombs number: ";
            cin >> bombs_num;
        }
    }
    return;
}

void bombplacer ()
{
    int x_bomb , y_bomb;
    srand (time(NULL));

    for ( int i = 0 ; i < bombs_num ; i++ )
    {
        x_bomb = rand() % row;
        y_bomb = rand() % column;

        if(realboard[x_bomb][y_bomb] != '*')
        {
            realboard[x_bomb][y_bomb] = '*';
        }
        else
        {
            i -= 1;
        }
    }
    return;
}

void show_fakeboard ()
{
    int  numboard_y = column;

    for (int j = column-1 ; j >=0 ; j--)
	{
        cout << numboard_y;
        if (numboard_y <= 9)
        {
            cout << "   ";
        }
        if (numboard_y <= 99 && numboard_y >= 10)
        {
            cout << "  ";
        }
        if (numboard_y == 100)
        {
            cout << " ";
        }

		for (int i = 0 ; i < row ; i++)
        {
			cout << fakeboard[i][j] << " ";
        }

        numboard_y -= 1;
        cout << endl;
	}
    // adadhaye radif payeen ra nzashtam chon be adadhaye 2 va 3 raghami ke miresid beham mirikht
    // dorost kardan beham rikhtegi ham baes mishod jadval kheili bozorg va zesht beshe
    return;
}

void show_realboard ()
{
    int numboard_y = column;
    for (int j = column-1 ; j >=0 ; j--)
	{
        cout << numboard_y;
        if (numboard_y <= 9)
        {
            cout << "   ";
        }
        if (numboard_y <= 99 && numboard_y >= 10)
        {
            cout << "  ";
        }
        if (numboard_y == 100)
        {
            cout << " ";
        }

		for (int i = 0 ; i < row ; i++)
        {
			cout << realboard[i][j] << " ";
        }

        numboard_y -= 1;
        cout << endl;
	}
    // adadhaye radif payeen ra nzashtam chon be adadhaye 2 raghami ke miresid beham mirikht
    // dorost kardan beham rikhtegi ham baes mishod jadval kheili bozorg va zesht beshe
    return;
}

void numbers_realboard ()
{
    int bomb_around=0 ;
    char bomb_around_char[2];
    for (int i = 0 ; i < row ; i++)
    {
        for (int j = 0 ; j < column ; j++)
        {
            bomb_around=0;

            if (realboard[i][j] != '*')
            {
                if(i-1 >= 0)
                    if (realboard[i-1][j] == '*')
                    {
                        bomb_around += 1;
                    }

                if(i+1 < row)
                    if (realboard[i+1][j] == '*')
                    {
                        bomb_around += 1;
                    }

                if (j-1 >= 0)
                    if (realboard[i][j-1] == '*')
                    {
                        bomb_around += 1;
                    }

                if (j+1 < column)
                    if (realboard[i][j+1] == '*')
                    {
                        bomb_around += 1;
                    }

                if(i-1 >= 0 && j-1 >= 0)
                    if (realboard[i-1][j-1] == '*')
                    {
                        bomb_around += 1;
                    }

                if(i-1 >= 0 && j+1 < column)
                    if (realboard[i-1][j+1] == '*')
                    {
                        bomb_around += 1;
                    }

                if(i+1 < row && j-1 >= 0)
                    if (realboard[i+1][j-1] == '*')
                    {
                        bomb_around += 1;
                    }

                if(i+1 < row && j+1 < column)
                    if (realboard[i+1][j+1] == '*')
                    {
                        bomb_around += 1;
                    }

                if (bomb_around != 0)
                {
                    sprintf(bomb_around_char, "%d", bomb_around);
                    realboard[i][j] = *bomb_around_char;
                }
                if (bomb_around == 0)
                {
                    realboard[i][j] = '0';
                }
            }      
        }
    }
    return;
}

void if_0(int z2 ,int z)
{
    if ( z != z2 )
    {
        return;
    }

    else
    {
        z += 1;
        for (int j = 0 ; j < column ; j++)
        {
            for (int i = 0 ; i < row ; i++)
            {
                if ( fakeboard[i][j] == '0')
                {
                    if(i-1 >= 0)
                        if (fakeboard[i-1][j] == '#')
                        {
                            fakeboard[i-1][j] = realboard[i-1][j];
                            z2 = z ;
                        }
                    if(i+1 < row)
                        if (fakeboard[i+1][j] == '#')
                        {
                            fakeboard[i+1][j] = realboard[i+1][j];
                            z2 = z ;
                        }
                    if (j-1 >= 0)
                        if (fakeboard[i][j-1] == '#')
                        {
                            fakeboard[i][j-1] = realboard[i][j-1];
                            z2 = z ;
                        }
                    if (j+1 < column)
                        if (fakeboard[i][j+1] == '#')
                        {
                            fakeboard[i][j+1] = realboard[i][j+1];
                            z2 = z ;
                        }
                    if(i-1 >= 0 && j-1 >= 0)
                        if (fakeboard[i-1][j-1] == '#')
                        {
                            fakeboard[i-1][j-1] = realboard[i-1][j-1];
                            z2 = z ;
                        }
                    if(i-1 >= 0 && j+1 < column)
                        if (fakeboard[i-1][j+1] == '#')
                        {
                            fakeboard[i-1][j+1] = realboard[i-1][j+1];
                            z2 = z ;
                        }
                    if(i+1 < row && j-1 >= 0)
                        if (fakeboard[i+1][j-1] == '#')
                        {
                            fakeboard[i+1][j-1] = realboard[i+1][j-1];
                            z2 = z ;
                        }
                    if(i+1 < row && j+1 < column)
                        if (fakeboard[i+1][j+1] == '#')
                        {
                            fakeboard[i+1][j+1] = realboard[i+1][j+1];
                            z2 = z ;
                        }
                }
            }
        }
        if_0(z2 ,z);
    }
}

void discover_move()
{
    cout << "Please enter a place to discover (row column)(-1 for return): ";
    cin >> move_x;
    if (move_x != -1)
        cin >> move_y;
    cout << endl;

    if (move_x == -1)
    {
        return;
    }

    if (fakeboard[move_x-1][move_y-1] != '@')
    {
        if (move_x <= row && move_y <= column)
        {
            if (moves_done == 0)
            {
                while (realboard[move_x-1][move_y-1] == '*')
                {
                    for (int i = 0 ; i < row ; i++)
                    {
                        for(int j = 0 ; j < column ; j++)
                        {
                            realboard[i][j] =  '#';
                        }
                    }
                    cout << endl;

                    bombplacer ();
                    numbers_realboard ();
                }
            }
            
            moves_done += 1;
            fakeboard[move_x-1][move_y-1] = realboard[move_x-1][move_y-1];

            if (realboard[move_x-1][move_y-1] == '0')
            {
                if_0(0 ,0);
            }

            if (realboard[move_x-1][move_y-1] == '*')
            {
                realboard[move_x-1][move_y-1] = '&';

                cout << "!! Game Over !! " << endl;
                cout << "\\|/The GameBoard\\|/" << endl;
                show_realboard();
                cout << endl;

                for (int j = row-1 ; j >=0 ; j--)
                {
                    for(int i = 0 ; i < column ; i++)
                    {
                        realboard[i][j] = fakeboard[i][j] = '#';
                    }
                }
                moves_done=0;

                main_menu();
            }
            else
            {  
                cout << "\\|/The GameBoard\\|/" << endl;
                show_fakeboard ();
                cout << endl;
            }
            
        }
        else
        {
            cout << "\\|/The GameBoard\\|/" << endl;
            show_fakeboard ();
            cout << endl << "This place doesn't exist!!!'" << endl << endl;
        }
    }
    else
    {
        cout << "\\|/The GameBoard\\|/" << endl;
        show_fakeboard ();
        cout << endl << "Please remove flag !!!" << endl << endl;
    }
    return;
}

void flag_move()
{
    cout << "Please enter a place to flag (row column)(-1 for return): ";
    cin >> move_x;

    if (move_x != -1)
    {
        cin >> move_y;
    }
    cout << endl;

    if (move_x == -1)
    {
        return;
    }

    if (fakeboard[move_x-1][move_y-1] == '#')
    {
        if (move_x <=row && move_y <=column)
        {
            all_flags += 1;
            fakeboard[move_x-1][move_y-1] = '@';

            if (realboard[move_x-1][move_y-1] == '*')
            {
                flags_bomb += 1;
            }

            if( flags_bomb == bombs_num && all_flags == flags_bomb )
            {
                cout << "!! You Won !!" << endl;
                cout << "\\|/The GameBoard\\|/" << endl;
                show_realboard ();
                cout << endl;

                for (int j = row-1 ; j >=0 ; j--)
                {
                    for(int i = 0 ; i < column ; i++)
                    {
                        realboard[i][j] = fakeboard[i][j] = '#';
                    }
                }
                moves_done=0;
                main_menu();
            }
            else
            {
                cout << "\\|/The GameBoard\\|/" << endl;
                show_fakeboard ();
            }
            
        }
        else
        {
            cout << "\\|/The GameBoard\\|/" << endl;
            show_fakeboard ();
            cout << endl;
            cout << "This place doesn't exist!!!'" << endl;
        }
    }
    else
    {
        cout << "\\|/The GameBoard\\|/" << endl;
        show_fakeboard ();
        cout << endl;
        cout << "you can't flag a discovered place !!!" << endl;
    }
    return;
}

void remove_flag()
{
    cout << "Please enter a place to remove flag (row column)(-1 for return): ";
    cin >> move_x;
    if (move_x != -1)
        cin >> move_y;
    cout << endl;

    if (move_x == -1)
    {
        return;
    }

    if (fakeboard[move_x-1][move_y-1] == '@')
    {
        if (move_x <=row && move_y <=column)
        {
            all_flags -= 1;
            fakeboard[move_x-1][move_y-1] = '#';

            if (realboard[move_x-1][move_y-1] == '*')
            {
                flags_bomb -= 1;
            }

            if( flags_bomb == bombs_num && all_flags == flags_bomb )
            {
                cout << "!! You Won !!" << endl;
                cout << "\\|/The GameBoard\\|/" << endl;
                show_realboard ();
                cout << endl;

                for (int j = row-1 ; j >=0 ; j--)
                {
                    for(int i = 0 ; i < column ; i++)
                    {
                        realboard[i][j] = fakeboard[i][j] = '#';
                    }
                }
                moves_done=0;
                main_menu();
            }
            cout << "\\|/The GameBoard\\|/" << endl;
            show_fakeboard ();

        }
        else
        {
            cout << "\\|/The GameBoard\\|/" << endl;
            show_fakeboard ();
            cout << endl << "This place doesn't exist!!!'" << endl;
        }
    }
    else
    {
        cout << "\\|/The GameBoard\\|/" << endl;
        show_fakeboard ();
        cout << endl <<  "There is no flag here !!!" << endl;
    }
    return;
}

void loadgame()
{
    int m=0 , v=0;
    char board[1] , info[27];
    string  s_info_filename1 , s_info_filename2 , s_info_filename3 ,s_realboard_filename , s_fakeboard_filename , s_game_filename , s_info1 , s_info2 , s_info3 ,  s_d , time ;
    
    save:
    s_info_filename1 = ("save-info-1-" + s_username + ".txt");
    s_info_filename2 = ("save-info-2-" + s_username + ".txt");
    s_info_filename3 = ("save-info-3-" + s_username + ".txt");
    char info_filename1[s_info_filename1.length() + 1];
    char info_filename2[s_info_filename2.length() + 1];
    char info_filename3[s_info_filename3.length() + 1];
    strcpy(info_filename1, s_info_filename1.c_str());
    strcpy(info_filename2, s_info_filename2.c_str());
    strcpy(info_filename3, s_info_filename3.c_str());

    userfile = fopen(info_filename1 , "r");
    if (userfile == NULL)
    {
        cout << "slot1:Empty" << endl;
        fclose(userfile);
    }
    else
    {
        while (fgets(info , 27 , userfile) != NULL)
        {
            string s_info = info;
            if (m == 0)
            {
                s_info1 = info;
            }
            if (m == 1)
            {
                s_info2 = info;
                discovered = atoi(info);
            }
            if (m == 2)
            {
                s_info3 = info;
                all_flags = atoi(info);
            }     
            if (m == 3)
            {
                time = info;
            } 
            m +=1 ;
        }
        fclose(userfile);
        m=0;
        cout << "slot 1" << ':' << endl <<  s_info1 <<  s_info2<< s_info3 <<  time << endl;
    }

    userfile = fopen(info_filename2 , "r");
    if (userfile == NULL)
    {
        cout << "slot2:Empty" << endl;
        fclose(userfile);
    }
    else
    {
        while (fgets(info , 27 , userfile) != NULL)
        {
            string s_info = info;
            if (m == 0)
            {
                s_info1 = info;
            }
            if (m == 1)
            {
                s_info2=info;
                discovered = atoi(info);
            }
            if (m == 2)
            {
                s_info3=info;
                all_flags = atoi(info);
            }     
            if (m == 3)
            {
                time = info;
            } 
            m +=1 ;
        }
        fclose(userfile);
        m=0;
        cout << "slot 2" << ':' << endl <<  s_info1 <<  s_info2<< s_info3 <<  time << endl;
    }

    userfile = fopen(info_filename3 , "r");
    if (userfile == NULL)
    {
        cout << "slot3:Empty" << endl;
        fclose(userfile);
    }
    else
    {
        while (fgets(info , 27 , userfile) != NULL)
        {
            string s_info = info;
            if (m == 0)
            {
                s_info1=info;
            }
            if (m == 1)
            {
                s_info2=info;
                discovered = atoi(info);
            }
            if (m == 2)
            {
                s_info3=info;
                all_flags = atoi(info);
            }     
            if (m == 3)
            {
                time=info;
            } 
            m +=1 ;
        }
        fclose(userfile);
        m=0;
        cout << "slot 3" << ':' << endl <<  s_info1 <<  s_info2<< s_info3 <<  time << endl;
    }

    cout << "Please select a slot to load(1-3)(-1:Return): ";
    cin >> save_slot;

    if (save_slot != "1" && save_slot != "2" && save_slot != "3" && save_slot != "-1")
    {
        cout << "You should select a slot between 1-3!!!" << endl;
        main_menu();
    }
    if (save_slot == "-1")
    {
        main_menu();
    }
        
    s_fakeboard_filename = ("save-fakeboard-"+ save_slot + "-" + username + ".txt");
    s_realboard_filename = ("save-realboard-"+ save_slot + "-" + username + ".txt");
    s_game_filename = ("save-game-"+ save_slot + "-" + username + ".txt");
    char fakeboard_filename[s_fakeboard_filename.length() + 1];
    char realboard_filename[s_realboard_filename.length() + 1];
    char game_filename[s_game_filename.length() + 1];
    strcpy(fakeboard_filename, s_fakeboard_filename.c_str());
    strcpy(realboard_filename, s_realboard_filename.c_str());
    strcpy(game_filename, s_game_filename.c_str());

        
    userfile = fopen(game_filename , "r");
    if (userfile == NULL)
    {
        cout << "Slot " << save_slot << " is empty !!!" << endl;
        fclose(userfile);
        main_menu();
    }
    while (fgets(info , 10000 , userfile) != NULL)
    {
        string s_info = info;
        if (m == 0)
        {
            moves_done = atoi(info);
        }
        if (m == 1)
        {
            flags_bomb = atoi(info);
        }  
        if (m == 2)
        {
            row = atoi(info);
        }
        if (m == 3)
        {
            column = atoi(info);
        }
        if (m == 4)
        {
            bombs_num = atoi(info);
        }
        m+=1;
    }
    m=0;
    fclose (userfile);
        
    char board2[row * column];
    

    userfile = fopen(realboard_filename , "r");
    if (userfile == NULL)
    {
        cout << "Error!!" << endl;
        fclose(userfile);
        main_menu();
    }
    while (fgets(info , 2 , userfile) != NULL)
        while ( v < column*row)
        {
            string s_info = info;
            if (s_info[0] == *"\n")
            {
                break;
            }
            strcpy(board, s_info.c_str());
            board2[v] = board[0];
            v+=1;
            break;
        }
    fclose (userfile);
    v=0;
        
    for (int j = column-1 ; j >=0 ; j--)
	{
        for (int i = 0 ; i < row ; i++)
        {
            realboard[i][j]=board2[v];
            v += 1;
        }
	}
    v=0;


    userfile = fopen(fakeboard_filename , "r");
    while (fgets(info , 2 , userfile) != NULL)
        while ( v < column*row)
        {
            string s_info = info;
            if (s_info[0] == *"\n")
            {
                break;
            }
            strcpy(board, s_info.c_str());
            board2[v] = board[0];
            v+=1;
            break;
        }
    fclose (userfile);
    v=0;
        
    for (int j = column-1 ; j >=0 ; j--)
	{
        for (int i = 0 ; i < row ; i++)
        {
            fakeboard[i][j]=board2[v];
            v += 1;
        }
	}
    v=0;

    play_loadgame ();
}

void play_loadgame()
{
    cout << "\\|/The GameBoard\\|/" << endl;
    show_fakeboard ();
    select_action();
}

void ss(char *fakeboard_filename)
{
    userfile = fopen(fakeboard_filename , "w");
    for (int j = column-1 ; j >=0 ; j--)
	{
		for (int i = 0 ; i < row ; i++)
        {
            char cr[2];
            cr[0] = fakeboard[i][j];
            fprintf (userfile , cr);
            fprintf (userfile , "\n");
        }
	}
    fclose (userfile);
    return;
}

void save_game(string save_slot) 
{
    string s_info_filename , s_realboard_filename , s_fakeboard_filename , s_game_filename , s_d , ans2;

    s_info_filename = ("save-info-"+ save_slot + "-" + username + ".txt");
    s_fakeboard_filename = ("save-fakeboard-"+ save_slot + "-" + username + ".txt");
    s_realboard_filename = ("save-realboard-"+ save_slot + "-" + username + ".txt");
    s_game_filename = ("save-game-"+ save_slot + "-" + username + ".txt");
    char info_filename[s_info_filename.length() + 1];
    char fakeboard_filename[s_fakeboard_filename.length() + 1];
    char realboard_filename[s_realboard_filename.length() + 1];
    char game_filename[s_game_filename.length() + 1];
    strcpy(info_filename, s_info_filename.c_str());
    strcpy(fakeboard_filename, s_fakeboard_filename.c_str());
    strcpy(realboard_filename, s_realboard_filename.c_str());
    strcpy(game_filename, s_game_filename.c_str());

    

    switch (difficulty)
    {
        case 1:
        {
            s_d="Easy";
            break;
        }
        case 2:
        {
            s_d="Normal";
            break;
        }
        case 3:
        {
            s_d="Hard";
            break;
        }
        case 4:
        {
            s_d="Custom";
            break;
        }
    }

    char d[s_d.length() + 1];
    strcpy(d, s_d.c_str());

    time_t now = time(0);
    char *now_time = ctime(&now);

    for (int j = column-1 ; j >=0 ; j--)
	{
		for (int i = 0 ; i < row ; i++)
        {
			if (fakeboard[i][j] != '#' && fakeboard[i][j] != '@')
                discovered +=1;
        }
	}


    char c_discovered[row * column + sizeof(char)];
    std::sprintf(c_discovered, "%d", discovered);
    char c_all_flags[row * column + sizeof(char)];
    std::sprintf(c_all_flags, "%d", all_flags);

    userfile = fopen(info_filename , "w");
    fprintf (userfile , d);
    fprintf (userfile , "\n");
    fprintf (userfile , c_discovered);
    fprintf (userfile , "\n");
    fprintf (userfile , c_all_flags);
    fprintf (userfile , "\n");
    fprintf (userfile , now_time);
    fclose (userfile);


    userfile = fopen(realboard_filename , "w");
    for (int j = column-1 ; j >=0 ; j--)
	{
		for (int i = 0 ; i < row ; i++)
        {
            char cr[2];
            cr[0] = realboard[i][j];
            fprintf (userfile , cr);
            fprintf (userfile , "\n");
        }
	}
    fclose (userfile);
    
    ss(fakeboard_filename);
    

    char c_moves_done[row * column + sizeof(char)];
    std::sprintf(c_moves_done, "%d", moves_done);
    char c_flags_bomb[row * column + sizeof(char)];
    std::sprintf(c_flags_bomb, "%d", flags_bomb);
    char c_row[3 + sizeof(char)];
    std::sprintf(c_row, "%d", row);
    char c_column[3 + sizeof(char)];
    std::sprintf(c_column, "%d", column);
    char c_bombs_num[row * column + sizeof(char)];
    std::sprintf(c_bombs_num, "%d", bombs_num);


    userfile = fopen(game_filename , "w");
    fprintf (userfile , c_moves_done);
    fprintf (userfile , "\n");
    fprintf (userfile , c_flags_bomb);
    fprintf (userfile , "\n");
    fprintf (userfile , c_row);
    fprintf (userfile , "\n");
    fprintf (userfile , c_column);
    fprintf (userfile , "\n");
    fprintf (userfile , c_bombs_num);
    fclose (userfile);

    cout << "Game is saved" << endl << endl;
    return;
}

void select_action()
{
    sel_act:

    cout << "Select Action (1=Discover - 2=Flag - 3=Remove Flag - 4=Save - 5=Exit): ";
    cin >> action;

    switch(action)
    {
        case 1:
        {
            discover_move();
            if (autosave_status == "ON" || autosave_status == "on")
            {
                save_game(autosave_slot);
            }
            goto sel_act;
            break;
        }
        case 2:
        {
            flag_move();
            if (autosave_status == "ON" || autosave_status == "on")
            {
                save_game(autosave_slot);
            }
            goto sel_act;
            break;
        }
        case 3:
        {
            remove_flag();
            if (autosave_status == "ON" || autosave_status == "on")
            {
                save_game(autosave_slot);
            }
            goto sel_act;
            break;
        }
        case 4:
        {
            cout << "Please select a slot to save(1-3)(-1 for return):";
            cin >> save_slot;

            string s_info_filename = ("save-info-"+ save_slot + "-" + username + ".txt") , ans2;
            char info_filename[s_info_filename.length() + 1];
            strcpy(info_filename, s_info_filename.c_str());

            if (save_slot != "1" && save_slot != "2" && save_slot != "3" && save_slot != "-1")
            {
                cout << "Please select a slot between 1-3!!!" << endl << endl;
                select_action();
            }
            if (save_slot == "-1")
            {
                select_action();
            }

            userfile = fopen(info_filename , "r");
            if (userfile != NULL)
            {
                cout << "This slot is full.Do you want to replace save data? ( YES/NO ): ";
                cin >> ans2;
                if (ans2 == "no" || ans2 == "NO")
                {
                    fclose(userfile);
                    goto sel_act;
                }
            }
            fclose(userfile);

            save_game(save_slot);
            goto sel_act;
            break;
        }
        case 5:
        {
            if (autosave_status == "ON" || autosave_status == "on")
            {
                save_game(autosave_slot);
            }
            for (int j = column-1 ; j >=0 ; j--)
            {
                for(int i = 0 ; i < row ; i++)
                {
                    realboard[i][j] = fakeboard[i][j] = '#';
                }
            }
            discovered = 0;
            moves_done=0;
            flags_bomb=0;
            all_flags=0;
            main_menu();
            break;
        }
        default:
        {
            cout << "Invalid command" << endl;
            goto sel_act;
            break;
        }
    }
    return;
}

void play_newgame()
{
    for (int j = column-1 ; j >=0 ; j--)
    {
        for(int i = 0 ; i < row ; i++)
        {
            realboard[i][j] = fakeboard[i][j] = '#';
        }
    }
    cout << endl;

    bombplacer ();
    numbers_realboard ();

    cout << "\\|/The GameBoard\\|/" << endl;
    show_fakeboard ();
    select_action ();
}

void first_menu()
{
    int option , check_user=0;

    cout << endl << "Welcome to minesweeper!" << endl << endl;
    first_menu:
    cout << "select an option with a number(1=Sign Up - 2=Sign In - 3=Exit): ";
    cin >> option;

    switch (option)
    {
        case 1:
        {
            cout << "Please enter your username: ";
            cin >> username;
            cout << "Please enter your password: ";
            cin >> password;
            
            userfile = fopen("usernames.txt" , "r");

            if (userfile != NULL)
            {
                while (fgets(userpass_data , 202 , userfile) != NULL)
                {
                    s_userpass_data = userpass_data;
                    s_username = username;
                    if (s_userpass_data  == s_username + "\n")
                    {
                        cout << "This username already exists!!!" << endl << endl;
                        fclose (userfile);
                        goto first_menu;
                        break;
                    }
                }
            }
            fclose (userfile);
            
            
            userfile = fopen("users.txt" , "a");
            fprintf (userfile , username);
            fprintf (userfile , ":");
            fprintf (userfile , password);
            fprintf (userfile , "\n");
            fclose (userfile);

            userfile = fopen("usernames.txt" , "a");
            fprintf (userfile , username);
            fprintf (userfile , "\n");
            fclose (userfile);
            cout << "Thank you for your registration" << endl;

            break;
        }
        case 2:
        {
            cout << "Please enter your username: ";
            cin >> username;
            cout << "Please enter your password: ";
            cin >> password;

            userfile = fopen("users.txt" , "r");
            while (fgets(userpass_data , 202 , userfile) != NULL)
            {
                s_userpass_data = userpass_data;
                s_username = username;
                s_password = password;
                if (s_userpass_data == (s_username +":"+ s_password + "\n"))
                {
                    cout << "Welcome " << s_username << endl;
                    check_user += 1;
                    break;
                }
            }
            fclose (userfile);

            if(check_user == 0)
                {
                    cout << "Invalid username or password!!!" << endl << endl;
                    goto first_menu;
                }
            break;
        }
        case 3:
        {
            exit(0);
        }   
        default:
        {
            cout << "Invalid command" << endl << endl;
            goto first_menu;
            break;
        }
    }
    main_menu();
}

void main_menu()
{
    int option_main_menu;
    int file_lines_num=0 , q=0;
    string ans2;

    main_menu:
    cout << endl << "Main Menu" << endl << endl;
    cout << "select an option with a number(1=New game - 2=Load game - 3=Change password - 4=Turn on/off autosave - 5=Sign out): ";
    cin >> option_main_menu;

    switch(option_main_menu)
    {
        case 1:
        {
            cout << "Please select the difficulty level(-1=Return - 1=Easy(9x9 & 10 bombs) - 2=Normal(16x16 & 40 bombs) - 3=Hard(16x30 & 99 bombs) - 4=Custom(max 100X100)): ";
            cin >> difficulty;
            if (difficulty == -1||difficulty == 1 || difficulty == 2 || difficulty == 3 || difficulty == 4)
            {
                difficulty2 ();
                play_newgame ();
                goto main_menu;
                break;
            }
            else
            {
                cout << "Invalid command!!!" << endl;
                goto main_menu;
                break;
            }
            
        }

        case 2:
        {
            loadgame();
            break;
        }

        case 3:
        {
            userfile = fopen("users.txt" , "r");
            if (userfile == NULL)
            {
                cout << "Error!! A file is missing" << endl;
                goto main_menu;
            }
            while (fgets(userpass_data , 202 , userfile) != NULL)
            {
                file_lines_num += 1;
            }
            string s_filetmp[file_lines_num];
            fclose (userfile);


            userfile = fopen("users.txt" , "r");
            while (fgets(userpass_data , 202 , userfile) != NULL)
            {
                s_userpass_data = userpass_data;
                s_username = username;
                s_password = password;
                if (s_userpass_data == s_username + ':' + s_password + "\n")
                {
                    continue;
                }
                s_filetmp[q] = s_userpass_data;
                q += 1;
            }
            fclose (userfile);
            
            cout << "Please enter your new password:";
            cin >> password;
            s_password = password;
            s_filetmp[file_lines_num-1] = s_username + ':' + s_password + "\n";

            userfile = fopen("users.txt" , "w");
            for (int i=0 ; i < file_lines_num ; i++)
            {
                char filetmp[s_filetmp[i].length() + 1];
                strcpy(filetmp, s_filetmp[i].c_str());
                fprintf (userfile , filetmp);
            }
            fclose (userfile);
            cout << endl << "Done!" << endl;
            goto main_menu;
            break;

        }

        case 4:
        {
            cout << "Please select autosave status ( ON/OFF ): ";
            cin >> autosave_status;
            if (autosave_status != "ON" && autosave_status != "on" && autosave_status != "OFF" && autosave_status != "off")
                cout << "Invalid command!!!" << endl;
            if (autosave_status == "ON" || autosave_status == "on")
            {
                cout << "Please select a slot for autosave(1-3)(-1 for return):";
                cin >> autosave_slot;

                if (autosave_slot != "1" && autosave_slot != "2" && autosave_slot != "3" && autosave_slot != "-1")
                {
                    cout << "Please select a slot between 1-3!!!" << endl << endl;
                    goto main_menu;
                }
                if (autosave_slot == "-1")
                {
                    autosave_status = "OFF";
                    goto main_menu;
                }

                string s_info_filename = ("save-info-"+ autosave_slot + "-" + username + ".txt");
                char info_filename[s_info_filename.length() + 1];
                strcpy(info_filename, s_info_filename.c_str());

                userfile = fopen(info_filename , "r");
                if (userfile != NULL)
                {
                    cout << "This slot is full.Do you want to replace save data? ( YES/NO ): ";
                    cin >> ans2;
                    if (ans2 == "no" || ans2 == "NO")
                    {
                        autosave_status = "OFF";
                        fclose(userfile);
                        goto main_menu;
                    }
                }
                fclose(userfile);
            }
            
            goto main_menu;
        }
        case 5:
        {
            first_menu();
            break;
        }
        default:
        {
            cout << "Invalid command!!!" << endl;
            goto main_menu;
            break;
        }
    }
}
