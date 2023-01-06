using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Media;

namespace boom_chess
{
    public partial class GameForm : Form
    {
        public StartPage startPage;
        public PlayerPage playerPage;
        public GamePage gamePage;
        public EndPage endPage;

        public bool start = false;                          //游戏是否开始
        public GameBoard chessBoard;                      //创建一个棋盘
        

        public static GameForm gameForm;  //定义静态变量
        public GameForm()
        {
            InitializeComponent();  //初始化

            System.Media.SoundPlayer sp = new System.Media.SoundPlayer(Properties.Resources.chord);
            sp.Play();
            gameForm = this;

            startPage = new StartPage();
            Controls.Add(startPage);
        }

        public static Color getForeColor(Player player) //获取该格子的前景色
        {
            if (player == null)
            {
                return Color.Silver;
            }
            switch (player.id)
            {
                case 0:
                    return Color.Red;
                case 1:
                    return Color.Green;
                case 2:
                    return Color.Blue;
                case 3:
                    return Color.Orange;
                default:
                    return Color.Silver;
            }

        }

        public static Color getBackColor(Player player) //获取该格子的背景色
        {
            if (player == null)
            {
                return Color.Silver;
            }
            switch (player.id)
            {
                case 0:
                    return Color.Pink;
                case 1:
                    return Color.LightGreen;
                case 2:
                    return Color.LightBlue;
                case 3:
                    return Color.LightYellow;
                default:
                    return Color.Silver;
            }
        }

        public static void Delay(int mm)//代替sleep防止程序假死（虽然不知道原理）
        {
            DateTime current = DateTime.Now;
            while (current.AddMilliseconds(mm) > DateTime.Now)
            {
                Application.DoEvents();
            }
            return;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
