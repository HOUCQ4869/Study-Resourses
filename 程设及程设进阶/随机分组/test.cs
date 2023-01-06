using System;
using System.IO;
using System.Text;

namespace test
{
    class Program
    {
        //定义组类，用于储存测试信息
        public class Group
        {
            private int major_j;                //记录组内计科人数
            private int major_x;                //记录组内信院人数
            private int major_s;                //记录组内数院人数
            private int sex_m;                  //记录组内男生人数
            private int sex_w;                  //记录组内女生人数
            private int ability_sum ;           //记录组内能力总值
            //构造函数初始化赋值
            public Group(int major_j, int major_x, int major_s, int sex_m, int sex_w, int ability_sum)
            {
                this.major_j = major_j;
                this.major_x = major_x;
                this.major_s = major_s;
                this.sex_m = sex_m;
                this.sex_w = sex_w;
                this.ability_sum = ability_sum;
            }
            //定义方法，便于操作
            public int Major_j
                { get { return major_j; } set { major_j = value; } }
            public int Major_x
                { get { return major_x; } set { major_x = value; } }
            public int Major_s
                { get { return major_s; } set { major_s = value; } }
            public int Sex_m
                { get { return sex_m; } set { sex_m = value; } }
            public int Sex_w
                { get { return sex_w; } set { sex_w = value; } }
            public int Ability_sum
                { get { return ability_sum; } set { ability_sum = value; } }

        }
        //用于定义全局变量
        public class Common
        {
            public static int group_num = 0;            //实时记录当前组的序号
        }
        //进行对于性别分组的测试
        void major_group_test(string line, Group [] group)
        {
            //首先判断读入行是否为组数
            if (line[0] == '第')
            {
                Common.group_num++;
            }
            else
            {
                for(int i = 30; i < line.Length; i++)
                {
                    //筛选各专业人员
                    if (line[i] == '计')
                    {
                        group[Common.group_num].Major_j++;
                    }
                    else if (line[i] == '信')
                    {
                        group[Common.group_num].Major_x++;
                    }
                    else if(line[i] == '数')
                    {
                       group[Common.group_num].Major_s++;
                    }
                }
            }
        }
        //进行对于能力值分组的测试
        void ability_group_test(string line, Group [] group)
        {
            //首先判断读入行是否为组数
            if(line [0] == '第')
            {
                Common.group_num++;
            }
            else
            {
                //更新各组的能力总值
                for(int i = 25; i < line.Length; i++)
                {
                    if (line[i] > 50 && line[i] < 58)
                        group[Common.group_num].Ability_sum += line[i] - '0';
                }
            }
        }
        //进行对于性别分组的测试
        void sex_group_test(string line, Group [] group)
        {
            //首先判断读入行是否为组数
            if(line [0] == '第')
            {
                Common.group_num++;
            }
            else
            {
                //更新各组的男女生人数
                for(int i = 20; i < line.Length; i++)
                {
                    if( line[i] == '1')
                    {
                        group[Common.group_num].Sex_m++;
                    }
                    else if(line[i] == '2')
                    {
                        group[Common.group_num].Sex_w++;
                    }
                }
            }
        }
        //对于专业测试结果的打印
        void Write_group_major(Group [] group)
        {         
            for (int i = 0; i < Common.group_num; i++)
            {
                Console.Write($"第{i + 1}组: ");
                Console.WriteLine($"计{group[i + 1].Major_j}人,信{group[i + 1].Major_x}人,数{group[i + 1].Major_s}人");
            }
        }
        //对于性别分组结果的打印
        void Write_group_sex(Group [] group)
        {
            for(int i = 0; i < Common.group_num; i++)
            {
                Console.Write($"第{i + 1}组: ");
                Console.WriteLine($"男{group[i + 1].Sex_m}人,女{group[i + 1].Sex_w}人");
            }
        }
        //对于能力值分组的打印
        void Write_group_ability(Group [] group)
        {
            for(int i = 0; i < Common.group_num; i++)
            {
                Console.Write($"第{i + 1}组: ");
                Console.WriteLine($"能力总值{group[i + 1].Ability_sum}");
            }
        }
        //初始化组类
        void Inital(Group [] group)
        {
            for(int i = 0; i < 50; i++)
            {
                group[i] = new Group(0, 0, 0, 0, 0, 0);
            }
        }
        //主函数
        static void Main(string [] args)
        {
            Program program = new Program();
            Group [] group = new Group[50];                     //考虑结果储存在同一类中三种分组至多40组
            program.Inital(group);
            int flag = 0;                                       //用于判断此时进行的是什么类别的分组
            bool flag1 = false, flag2 = false, flag3 = false;   //三个布尔值用于判断是否更新当前组的序号
            //此为分组名单的路径
            foreach (string line in File.ReadLines(@"D:\Codefiled\CODE_C#\随机分组1\随机分组1\bin\Debug\net6.0\分组名单.txt"))
            {
                //判断进行分组的类型
                if (line[0] == '专')
                {
                    flag = 1;
                    flag1 = true;           //刚进行转换时标记显示
                    continue;
                }
                if (line[0] == '能')
                {
                    flag = 2;
                    flag2 = true;
                    continue;
                }
                if (line[0] == '性')
                {
                    flag = 3;
                    flag3 = true;
                    continue;
                }
                //如果存在标记正在显示，即正将开始新的分组，此时更新当前组为0
                if(flag1 || flag2 || flag3)
                {
                    Common.group_num = 0;
                }
                if (flag == 1)
                {
                    program.major_group_test(line, group);
                    flag1 = false;          //开始后隐藏标记
                }
                else if (flag == 2)
                {
                    program.ability_group_test(line, group);
                    flag2 = false;
                }
                else if (flag == 3)
                {
                    program.sex_group_test(line, group);
                    flag3 = false;  
                }

            }
            //打印分组测试情况
            Console.WriteLine("对于按专业分组有如下统计:");
            program.Write_group_major(group);
            Console.WriteLine("对于按性别分组有如下统计:");
            program.Write_group_sex(group);
            Console.WriteLine("对于按能力值分组有如下统计:");
            program.Write_group_ability(group);
            Console.ReadLine();
        }
    }

}