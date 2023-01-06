using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace boom_chess
{
    public class ChessBoard //棋盘类
    {
        public bool ifGameover = false;                 //判断游戏是否结束
        public int turn = 0;                            //表示当前进行的回合数
        public int playerTurn = 0;                      //表示轮到第几位玩家
        public int size = 6;                            //棋盘大小(n*n)
        
        public int players = 0;                         //玩家人数
        public List<Player> playerlist = new List<Player>();    //创建玩家列表

        public Checkeroard[,] checkeroards;             //棋盘格类数组，调用的时候只调用1到size.
        bool[,] ifboom = new bool[20, 20];              //储存是否要爆炸的信息，以保证所有格子爆炸的优先级相同（避免遍历的时候排前面的格子炸了直接影响后面的格子）

        public ChessBoard()
        {
            
        }

        public ChessBoard(int size)
        {
            SetSize(size);
        }

        public void SetSize(int size)
        {
            this.size = size;
            checkeroards = new Checkeroard[size, size];
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    Checkeroard checkeroard = new Checkeroard();
                    int flag = 0;
                    if (i == 0 || i == size - 1)
                        flag++;
                    if (j == 0 || j == size - 1)
                        flag++;
                    if (flag == 1)
                        checkeroard.booms = 3;
                    if (flag == 2)
                        checkeroard.booms = 2;

                    checkeroards[i, j] = checkeroard;
                }
            }
        }

        public ChessBoard Clone()
        {
            ChessBoard board = new ChessBoard(size);
            board.ifGameover = ifGameover;
            board.turn = turn;
            board.playerTurn = playerTurn;
            board.size = size;
            board.players = players;
            foreach(Player player in playerlist)
            {
                Player player1 = new Player(player.id);
                player1.life = player.life;
                player1.gridNumber = player.gridNumber;
                board.playerlist.Add(player1);
            }
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    Checkeroard checkeroard=new Checkeroard();
                    checkeroard.numbers = checkeroards[i, j].numbers;
                    checkeroard.owner = checkeroards[i, j].owner == null ? null : board.playerlist[checkeroards[i, j].owner.id];
                    checkeroard.booms = checkeroards[i, j].booms;
                    board.checkeroards[i, j] = checkeroard;
                }
            }
            return board;
        }

        public void AddPlayer(Player player)
        {
            players++;
            playerlist.Add(player);
        }

        public bool IfLife(int i) //判断玩家是否存活
        {
            return playerlist[i].life;
        }

        public bool Judge(int x, int y)//判断落子是否合法
        {
            if (checkeroards[x, y].owner == null || checkeroards[x, y].owner == playerlist[playerTurn])     //如果落子点为空白地盘或落子点位自己的地盘，则落子合法
                return true;
            return false;
        }
        public void MoveLater(int x, int y)  //进行一次落子
        {
            checkeroards[x, y].owner = playerlist[playerTurn]; //该格归该回合玩家
            checkeroards[x, y].numbers++;   //该格棋子+1
        }

        public void NextPlayer()
        {
            if (playerTurn < players - 1)
            {
                playerTurn++;
            }
            else
            {
                turn++;
                playerTurn = 0;
            }
            while (playerlist[playerTurn].life == false)
            {
                if (playerTurn == players-1)
                {
                    turn++;
                    playerTurn = 0;
                }
                else
                {
                    playerTurn++;
                }
            }
        }

        public int RunBoom()//进行一次遍历爆炸,如果发现并没有可以炸的，则返回-1，如果发现能炸，就返回爆炸吃子的个数；同时判断游戏是否结束
        {
            //进行爆炸!

            int flag = 0;   //如果发生爆炸，则flag改为1，如果遍历一遍没有爆炸，则flag为0结束循环，进入下一个玩家的回合
            int count = 0;

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    ifboom[i, j] = checkeroards[i, j].IfBoom(); //用一个数组储存当前棋盘格是否要爆炸的信息，如果直接边遍历边爆炸将使爆炸有先后顺序，无法保证各格子爆炸同步
                }
            }
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (ifboom[i, j])    // 如果发生爆炸了，调整各格子棋子数量，以及各格子属于的玩家
                    {
                        flag = 1;
                        checkeroards[i, j].numbers -= checkeroards[i, j].booms;
                        if (checkeroards[i, j].numbers == 0)
                        {
                            checkeroards[i, j].owner = null;//如果炸完后格子没有棋子，则该格子变成空白格
                        }


                        //爆炸棋子蔓延到周围格子
                        if (i - 1 >= 0)
                        {
                            if(checkeroards[i - 1, j].owner!= playerlist[playerTurn])
                            {
                                count += checkeroards[i - 1, j].numbers;
                                checkeroards[i - 1, j].owner = playerlist[playerTurn];
                            }
                            checkeroards[i - 1, j].numbers++;
                            
                        }
                        if (j - 1 >= 0)
                        {
                            if (checkeroards[i, j-1].owner != playerlist[playerTurn])
                            {
                                count += checkeroards[i, j-1].numbers;
                                checkeroards[i, j-1].owner = playerlist[playerTurn];
                            }
                            checkeroards[i, j-1].numbers++;
                        }
                        if (i + 1 < size)
                        {
                            if (checkeroards[i + 1, j].owner != playerlist[playerTurn])
                            {
                                count += checkeroards[i + 1, j].numbers;
                                checkeroards[i + 1, j].owner = playerlist[playerTurn];
                            }
                            checkeroards[i + 1, j].numbers++;
                        }
                        if (j + 1 < size)
                        {
                            if (checkeroards[i, j + 1].owner != playerlist[playerTurn])
                            {
                                count += checkeroards[i, j + 1].numbers;
                                checkeroards[i, j + 1].owner = playerlist[playerTurn];
                            }
                            checkeroards[i, j + 1].numbers++;
                        }
                    }
                }
            }

            //修改当前棋盘以及玩家的信息（比如是否存活，拥有的棋子）

            foreach (Player player in playerlist)
            {
                player.gridNumber = 0;
            }

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (checkeroards[i, j].owner != null)
                    {
                        checkeroards[i, j].owner.gridNumber += checkeroards[i, j].numbers;//遍历棋盘格，将棋子数量加到相应玩家占有的棋子数量上
                    }
                }
            }

            //判断游戏进行情况(是否有玩家寄掉，或者游戏结束）
            if (turn >= 1)
            {
                int flag_2 = 0;
                foreach (Player player in playerlist)
                {
                    if (player.gridNumber == 0)
                    {
                        player.life = false;
                    }

                }
                foreach (Player player in playerlist)
                {
                    if (player.life)
                    {
                        flag_2++;
                    }
                }
                if (flag_2 == 1)    //只剩一位玩家，游戏结束
                {
                    ifGameover = true;
                    flag = 0;
                }
            }

            if (flag == 0)
            {
                return -1;
            }
            else
            {
                return count;
            }
        }


        public string getNumber(int x, int y)   //获取该格子的棋子数
        {
            return checkeroards[x, y].numbers.ToString();
        }
    }

    public class GameBoard : ChessBoard                 //在GameForm中使用的棋盘类的子类
    {
        public int boardSize = 600;                     //棋盘大小（像素点）
        public Dictionary<Player, List<int>> gridNumberRecords = new Dictionary<Player, List<int>>();//记录玩家每个回合的棋子数
        public List<Player> playerRanks = new List<Player>();           //记录玩家排名

        public void AddPlayer(Player player)
        {
            base.AddPlayer(player);
            gridNumberRecords.Add(player, new List<int>());
        }

        public int RunBoom()
        {
            int res = base.RunBoom();
            foreach (Player player in playerlist)
            {
                gridNumberRecords[player].Add(player.gridNumber);
                if (!player.life)
                {
                    if (!playerRanks.Contains(player))
                    {
                        playerRanks.Insert(0, player);
                    }
                }
            }
            if (ifGameover)
            {
                foreach (Player player in playerlist)
                {
                    if (player.life)
                    {
                        playerRanks.Insert(0, player);
                    }
                }
            }
            return res;
        }
    }
}
