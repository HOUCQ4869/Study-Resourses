using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace boom_chess
{
    public class Player             //玩家类，储存玩家地盘数，存活信息
    {
        public readonly int id;     //玩家序号
        public int gridNumber;      //玩家占据棋子数
        public bool life;           //判断是否存活

        public Player(int id)
        {
            this.id = id;
            this.life = true;
        }
    }

    public class Human : Player
    {
        public Human(int id):base(id)
        {

        }
    }


    public class AI : Player
    {
        public readonly int level;
        static Random rd = new Random();

        public AI(int id,int level):base(id)
        {
            this.level = level;
        }

        public int[] GetStep(ChessBoard chessBoard)
        {
            int size = GameForm.gameForm.chessBoard.size;

            List<KeyValuePair<int[], int>> scores = new List<KeyValuePair<int[], int>>();
            

            for(int i=0;i<size ; i++)
            {
                for(int j=0;j< size; j++)
                {
                    int count = 0; //爆炸后棋子数
                    int score = 0;
                    if (chessBoard.Judge(i, j))
                    {
                        score += 500000;        //如果该点能下则大幅度提分，避免AI下到不能下的点

                        ChessBoard board = GameForm.gameForm.chessBoard.Clone();
                     
                        board.MoveLater(i, j);

                        while(true)     //模拟爆炸一次
                        {
                            int temp = board.RunBoom();
                            if (temp != -1)
                            {
                                score += (temp+1) * 20;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        for (int a = 0; a < size; a++)
                        {
                            for (int b = 0; b < size; b++)
                            {
                                if(board.checkeroards[i, j].owner!=null&&board.checkeroards[i,j].owner.id==id)
                                {
                                    count += board.checkeroards[a, b].numbers; //计算爆炸后的棋子数
                                    int flag = 0;
                                    if (a == 0 || a == size - 1)
                                    {
                                        flag++;
                                    }
                                    if (b == 0 || b == size - 1)
                                    {
                                        flag++;
                                    }
                                    switch (flag)
                                    {
                                        case 0:
                                            score += 6 * board.checkeroards[a, b].numbers;
                                            break;
                                        case 1:
                                            score += 10 * board.checkeroards[a, b].numbers;
                                            break;
                                        case 2:
                                            score += 20 * board.checkeroards[a, b].numbers;
                                            break;
                                        default:
                                            break;
                                    }
                                    for (int p = -1; p <= 1; p++)
                                    {
                                        for(int q = -1; q <= 1; q++)
                                        {
                                            if (!(p == 0 && q == 0) && i + p >= 0 && i + p < size && j + q >= 0 && j + q < size)
                                            {
                                                if (board.checkeroards[i+p,j+q].owner!=null&&board.checkeroards[i + p, j + q].owner.id == id)
                                                {
                                                    score += 1;
                                                   // score += board.checkeroards[i + p, j + q].numbers*2;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        score += count * 40; //每吃掉一个子多30分

                        if (board.ifGameover)
                        {
                            score += 500000;
                        }
                        else if(level == 2 || level == 3)       //判断下一步会被吃掉多少子，让大师和超神AI具备一定防守能力
                        {
                            int flag = 0;
                            int count1 = 0;     //定义两个count，如果下一步可能被吃子，每最多被吃一个扣掉30分
                            int count2 = count;
                            board.NextPlayer();
                            for(int a = 0; a < board.size; a++)
                            {
                                for(int b=0;b<board.size; b++)
                                {
                                    count1 = 0;
                                    if(board.Judge(a, b))
                                    {
                                        ChessBoard board1 = board.Clone();
                                        board1.MoveLater(a, b);
                                        while (board1.RunBoom() != -1)
                                        {

                                        }
                                        if (!board1.playerlist[id].life&&level==3) //超神AI下一步可能会被杀时会避免该落子
                                        {
                                            flag=1;
                                        }
                                        for (int c = 0; c < board1.size; c++)
                                        {
                                            for (int d = 0; d < board1.size; d++)
                                            {
                                                if (board1.checkeroards[c, d].owner != null && board1.checkeroards[c, d].owner.id == id)
                                                {
                                                    count1 += board1.checkeroards[c, d].numbers;
                                                }
                                            }
                                        }
                                        if (count1 < count2)
                                        {
                                            count2 = count1;
                                        }
                                    }
                                }
                                
                            }
                            score += count2 * level * 30;    //判断下一位玩家落子后己方可能剩余棋子数的最小值，这个值越大则分越高，可让AI有防止被吃子的决策。
                            if (flag == 1)
                            {
                                score -= 200000;
                            }

                        }
                        
                    }
                    switch (level)
                    {
                        case 0:     //菜鸟
                            score += rd.Next((int)Math.Pow(chessBoard.turn, 3) / 10);    //小范围浮动得分，避免出现重复
                            break;
                        case 1:     //中等
                            score += rd.Next((int)Math.Pow(chessBoard.turn, 2) / 10);    //小范围浮动得分，避免出现重复
                            break;
                        case 2:     //大师
                            score += rd.Next((int)Math.Pow(chessBoard.turn, 1.3) / 10);    //小范围浮动得分，避免出现重复
                            break;
                        case 3:     //超神
                            score += rd.Next((int)Math.Pow(chessBoard.turn, 1.1) / 10);    //小范围浮动得分，避免出现重复
                            break;
                        default:
                            score += rd.Next((int)Math.Pow(chessBoard.turn, 1.1) / 10);    //小范围浮动得分，避免出现重复
                            break;
                    }
                    
                    scores.Add(new KeyValuePair<int[], int>(new int[] { i, j }, score));
                }
            }
            scores.Sort(delegate(KeyValuePair<int[],int> item1,KeyValuePair<int[],int>item2)
            {
                if (item1.Value > item2.Value)
                {
                    return -1;
                }
                else if(item1.Value < item2.Value)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            });

            
            return scores[0].Key;
        }
    }
}
