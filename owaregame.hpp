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
        int min_pit = 0;
        int max_pit = 5;
        int opp_min_pit = 6;
        int opp_max_pit = 11;
        if(!is_bottom_turn)
        {
            min_pit = 6;
            max_pit = 11;
            opp_min_pit = 0;
            opp_max_pit = 5;
        }


        //check for invalid move
        int seeds = pits[pit];
        if(seeds == 0)
        {
            return MoveResult::START_PIT_EMPTY;
        }

        //check for valid move
        if(pit < min_pit || pit > max_pit)
        {
            return MoveResult::START_PIT_OUT_OF_BOUNDS;
        }


        //simulate move with temp board
        Board pits_copy = pits;
        pits_copy[pit] = 0;
        int offset = 1;
        //sow seeds
        while(seeds > 0)
        {
            if(offset >= 12)
            {
                offset = 0;
            }

            if(offset != 0)
            {
                ++pits_copy[pit+offset];
                --seeds;
            }
            ++offset;
        }
        int const end_pit = offset - 1;

        int opponent_seeds = 0;
        for(int p = opp_min_pit; p <= opp_max_pit; ++p)
        {
            opponent_seeds += pits_copy[p];
        }
        if(opponent_seeds == 0)
        {
            return MoveResult::OPPONENT_NEEDS_SEEDS;
        }



        //check and handle capture

        if(end_pit <= opp_max_pit && end_pit >= opp_min_pit )
        {
            int winnings = 0;
            bool chain = true;
            int current_pit = end_pit;
            while(chain == true)
            {
                if(current_pit == min_pit)
                {
                    chain = false;
                }
                if(pits_copy[current_pit] == 3 || pits_copy[current_pit] == 4)
                {
                    winnings += pits_copy[current_pit];
                    pits_copy[current_pit] = 0;
                    --current_pit;
                }
                else
                {
                    chain = false;
                }

            }
            if(is_bottom_turn)
            {
                bottom_score += winnings;
            }
            else
            {
                top_score += winnings;
            }
        }

        assert(is_game_valid(bottom_score, top_score, pits_copy) && "game state invalid!!!");


        pits = pits_copy;
        return static_cast<MoveResult>(end_pit);


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
    bool is_bottom_turn = true;




};


#endif // OWAREGAME_HPP
