#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "neuralNetwork.h"

using namespace std;

class coords {
public:
    int row;
    int column;
    bool operator== (const coords& other);
    bool operator!= (const coords& other);
};

class step {
public:
    coords from;
    coords to;
    bool operator== (const step& other);
};

struct properties {
    bool white_king;
    bool white_rook_right;
    bool white_rook_left;
    bool black_king;
    bool black_rook_right;
    bool black_rook_left;
    coords white_king_coords;
    coords black_king_coords;
    bool isWhite;
    vector<step> history;
    bool isChecked;
    int count_check_figs;
    int repeat;
};

class chess {
    public:
        vector<vector<char>> pos;
        properties prop;
        vector<coords> current_figs, opposite_figs;
        vector<step> current_steps, opposite_steps;
        vector<coords> current_fields, opposite_fields;
        vector<vector<char>> isOppositeField, isCheckField;
        vector<vector<coords>> ways;
        vector<vector<double>> training_data;
        vector<double> resources;
        map<char, double> fig_values;
        bool isVirtual;
        int MAX_STEPS;
        ofstream log;

        chess();
        chess(int max_steps);
        chess(vector<vector<char>> start_pos);
        chess(vector<vector<char>> start_pos, properties prop, bool virt);

        void replay();
        void setMaxSteps(int max_steps);
        vector<vector<char>> getDefaultPos();
        vector<vector<char>> getReversePos();
        vector<coords> getFigs(string reg);
        void initFigValues();
        bool containsFig(string reg, coords v);
        void printPos();
        string getStringPos(bool reverse);
        double getCoefficient();
        void printSteps();
        void printPos(vector<vector<char>> p);
        vector<double> toArray();
        bool isWhite(coords v);
        bool isBlack(coords v);
        bool isDiff(coords v1, coords v2);
        bool isEqualColor(coords v1, coords v2);
        bool isDiff(step st);
        void updateFigs();
        vector<step> getStepsByFig(coords cur, bool onlyAttackFields);
        bool isCheck();
        bool isMate();
        bool isDraw();
        bool possibleStep(step st, bool onlyAttackFields);
        void updateSteps();
        string getStatus();
        bool doStep(step st);
        bool isValidStep(step st);
        step doStepAI(neuralNetwork &AI);
        void trainAI(neuralNetwork& AI);
        step notationToSteps(string notation);
};
#endif