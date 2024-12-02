#ifndef OWAREGAME_HPP
#define OWAREGAME_HPP

#include <array>
#include <cassert>



class OwareGame
{

public:
    using Board = std::array<int, 12>;

    enum class MoveResult :int
    {
        GRAND_SLAM_NOT_ALLOWED = -4,
        START_PIT_OUT_OF_BOUNDS = -3,
        OPPONENT_NEEDS_SEEDS = -2,
        START_PIT_EMPTY = -1,
        PIT_0 = 0,
        PIT_1,
        PIT_2,
        PIT_3,
        PIT_4,
        PIT_5,
        PIT_6,
        PIT_7,
        PIT_8,
        PIT_9,
        PIT_10,
        PIT_11
    };

    static bool is_game_valid(int const bs, int const ts, Board const & board)
    {
        int total_seeds = 0;
        for(auto& p : board)
        {
            total_seeds = total_seeds + p;
        }
        total_seeds = total_seeds + ts;
        total_seeds = total_seeds + bs;

        if(total_seeds == 48)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    OwareGame()
    {
        for(auto& p : pits)
        {
            p = 4;
        }

    }

    int getTopPlayerScore() const
    {
        return top_score;
    }

    int getBottomPlayerScore() const
    {
        return bottom_score;
    }

    Board getBoard() const
    {
        return pits;
    }


    MoveResult move(int const pit)
    {


        return static_cast<MoveResult>(0);

    }

    bool isBottomPlayerTurn()
    {
        return is_bottom_turn;
    }

    bool isTopPlayerTurn()
    {
        return !is_bottom_turn;
    }

    void setBottomPlayerTurn(bool const b = true)
    {
        is_bottom_turn = b;
    }

    void setTopPlayerTurn(bool const b = true)
    {
        is_bottom_turn = (!b);
    }




private:
    Board pits;
    int bottom_score = 0;
    int top_score = 0;
    int move_count = 0;
    int max_moves = 200;
    int win_score = 25;
    int start_seeds = 4;
    int capture_low_value = 2;
    int capture_high_value = 3;
    bool is_bottom_turn = true;
    bool grand_slam_allowed = false;




};


#endif // OWAREGAME_HPP
