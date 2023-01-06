using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace boom_chess
{
    public class Checkeroard //棋盘格类
    {
        public Player owner = null;                             //属于的玩家
        public int numbers = 0;                                 //棋子的数量
        public int booms = 4;                                   //爆炸的上限

        public void ChangeBooms(int n)   //改变爆炸上限
        {
            booms = n;
        }
        public bool IfBoom()        //判断是否爆炸
        {
            return numbers >= booms;
        }
    }
}
