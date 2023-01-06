using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace test
{
    class Program
    {
        public class Student
        { //创建一个学生类,有学号,姓名,班级,年龄
            private int id;
            private string name;
            private int sex;//1代表男，2代表女
            private int ability;
            private string major;

            public Student(int id, string name, int sex, int ability, string major)
            //构造函数,用来初始化
            {
                this.id = id;
                this.name = name;
                this.sex = sex;
                this.ability = ability;
                this.major = major;
            }
            //定义属性
            /*属性是c#特有的,通常是变量的首字母大写
             get用来返回类成员的值
             set用来给类成员赋值,当然也可以对值进行判断,用value进行赋值*/
            public int Id
            {
                get
                {
                    return id;
                }
                set
                {
                    id = value;
                }
            }
            public string Name
            {
                get
                {
                    return name;
                }
                set
                {
                    name = value;
                }
            }
            public int Sex
            {
                get
                {
                    return sex;
                }
                set
                {
                    sex = value;
                }
            }
            public int Ability
            {
                get
                {
                    return ability;
                }
                set
                {
                    ability = value;
                }
            }
            public string Major
            {
                get
                {
                    return major;
                }
                set
                {
                    major = value;
                }
            }
        }
        //用于姓名赋值
        public class GetNameHelper
        {

            /// <summary>
            /// 姓
            /// </summary>
            private static List<string> SurnameList = new List<string>() {"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "楮", "卫", "蒋", "沈", "韩", "杨",
        "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏", "陶", "姜",
        "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛", "奚", "范", "彭", "郎",
        "鲁", "韦", "昌", "马", "苗", "凤", "花", "方", "俞", "任", "袁", "柳", "酆", "鲍", "史", "唐",
        "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤", "滕", "殷", "罗", "毕", "郝", "邬", "安", "常",
        "乐", "于", "时", "傅", "皮", "卞", "齐", "康", "伍", "余", "元", "卜", "顾", "孟", "平", "黄",
        "和", "穆", "萧", "尹", "姚", "邵", "湛", "汪", "祁", "毛", "禹", "狄", "米", "贝", "明", "臧",
        "计", "伏", "成", "戴", "谈", "宋", "茅", "庞", "熊", "纪", "舒", "屈", "项", "祝", "董", "梁",
        "杜", "阮", "蓝", "闽", "席", "季", "麻", "强", "贾", "路", "娄", "危", "江", "童", "颜", "郭",
        "梅", "盛", "林", "刁", "锺", "徐", "丘", "骆", "高", "夏", "蔡", "田", "樊", "胡", "凌", "霍",
        "虞", "万", "支", "柯", "昝", "管", "卢", "莫", "经", "房", "裘", "缪", "干", "解", "应", "宗",
        "丁", "宣", "贲", "邓", "郁", "单", "杭", "洪", "包", "诸", "左", "石", "崔", "吉", "钮", "龚",
        "程", "嵇", "邢", "滑", "裴", "陆", "荣", "翁", "荀", "羊", "於", "惠", "甄", "麹", "家", "封",
        "芮", "羿", "储", "靳", "汲", "邴", "糜", "松", "井", "段", "富", "巫", "乌", "焦", "巴", "弓",
        "牧", "隗", "山", "谷", "车", "侯", "宓", "蓬", "全", "郗", "班", "仰", "秋", "仲", "伊", "宫",
        "宁", "仇", "栾", "暴", "甘", "斜", "厉", "戎", "祖", "武", "符", "刘", "景", "詹", "束", "龙",
        "叶", "幸", "司", "韶", "郜", "黎", "蓟", "薄", "印", "宿", "白", "怀", "蒲", "邰", "从", "鄂",
        "索", "咸", "籍", "赖", "卓", "蔺", "屠", "蒙", "池", "乔", "阴", "郁", "胥", "能", "苍", "双",
        "闻", "莘", "党", "翟", "谭", "贡", "劳", "逄", "姬", "申", "扶", "堵", "冉", "宰", "郦", "雍",
        "郤", "璩", "桑", "桂", "濮", "牛", "寿", "通", "边", "扈", "燕", "冀", "郏", "浦", "尚", "农",
        "温", "别", "庄", "晏", "柴", "瞿", "阎", "充", "慕", "连", "茹", "习", "宦", "艾", "鱼", "容",
        "向", "古", "易", "慎", "戈", "廖", "庾", "终", "暨", "居", "衡", "步", "都", "耿", "满", "弘",
        "匡", "国", "文", "寇", "广", "禄", "阙", "东", "欧", "殳", "沃", "利", "蔚", "越", "夔", "隆",
        "师", "巩", "厍", "聂", "晁", "勾", "敖", "融", "冷", "訾", "辛", "阚", "那", "简", "饶", "空",
        "曾", "毋", "沙", "乜", "养", "鞠", "须", "丰", "巢", "关", "蒯", "相", "查", "后", "荆", "红",
        "游", "竺", "权", "逑", "盖", "益", "桓", "公", "仉", "督", "晋", "楚", "阎", "法", "汝", "鄢",
        "涂", "钦", "岳", "帅", "缑", "亢", "况", "后", "有", "琴", "归", "海", "墨", "哈", "谯", "笪",
        "年", "爱", "阳", "佟", "商", "牟", "佘", "佴", "伯", "赏",
        "万俟", "司马", "上官", "欧阳", "夏侯", "诸葛", "闻人", "东方", "赫连", "皇甫", "尉迟", "公羊",
        "澹台", "公冶", "宗政", "濮阳", "淳于", "单于", "太叔", "申屠", "公孙", "仲孙", "轩辕", "令狐",
        "锺离", "宇文", "长孙", "慕容", "鲜于", "闾丘", "司徒", "司空", "丌官", "司寇", "子车", "微生",
        "颛孙", "端木", "巫马", "公西", "漆雕", "乐正", "壤驷", "公良", "拓拔", "夹谷", "宰父", "谷梁",
        "段干", "百里", "东郭", "南门", "呼延", "羊舌", "梁丘", "左丘", "东门", "西门", "南宫"};

            /// <summary>
            /// 男性 名
            /// </summary>
            private static string LastNameMan = "刚伟勇毅俊峰强军平保东文辉力明永健世广志义兴良海山仁波宁贵福生龙元全国胜学祥才发武新利清飞彬富顺信子杰涛昌成康星光天达安岩中茂进林有坚和彪博诚先敬震振壮会思群豪心邦承乐绍功松善厚庆磊民友裕河哲江超浩亮政谦亨奇固之轮翰朗伯宏言若鸣朋斌梁栋维启克伦翔旭鹏泽晨辰士以建家致树炎德行时泰盛雄琛钧冠策腾楠榕风航弘";

            /// <summary>
            /// 女性 名
            /// </summary>
            private static string LastNameWoMan = "秀娟英华慧巧美娜静淑惠珠翠雅芝玉萍红娥玲芬芳燕彩春菊兰凤洁梅琳素云莲真环雪荣爱妹霞香月莺媛艳瑞凡佳嘉琼勤珍贞莉桂娣叶璧璐娅琦晶妍茜秋珊莎锦黛青倩婷姣婉娴瑾颖露瑶怡婵雁蓓纨仪荷丹蓉眉君琴蕊薇菁梦岚苑婕馨瑗琰韵融园艺咏卿聪澜纯毓悦昭冰爽琬茗羽希宁欣飘育滢馥筠柔竹霭凝鱼晓欢霄枫芸菲寒伊亚宜可姬舒影荔枝思丽墨";

            private static Random random = new Random();

            /// <summary>
            /// 随机取一个姓
            /// </summary>
            /// <returns></returns>
            private static string GetSurname()
            {
                return SurnameList[random.Next(0, SurnameList.Count)];
            }

            /// <summary>
            /// 随机取一个名
            /// </summary>
            /// <param name="sex">1:男/2:女</param>
            /// <returns></returns>
            private static string GetName(int sex)
            {
                //名 长度 ，1个或者2个字
                var nameLen = random.Next(1, 3);
                var name = "";
                for (int i = 0; i < nameLen; i++)
                {
                    if (sex == 1) name += LastNameMan[random.Next(0, LastNameMan.Length)];
                    else name += LastNameWoMan[random.Next(0, LastNameWoMan.Length)];
                }
                return name;
            }

            /// <summary>
            /// 随机生成一个男性姓名
            /// </summary>
            /// <returns></returns>
            public static string GetManName()
            {
                return GetSurname() + GetName(1);
            }

            /// <summary>
            /// 随机生成一个女性姓名
            /// </summary>
            /// <returns></returns>
            public static string GetWomanName()
            {
                return GetSurname() + GetName(2);
            }




        }
        //主窗口
        public static void window()
        {
            Console.WriteLine("***************************************");
            Console.WriteLine("*********欢迎使用学生分组系统!*********");
            Console.WriteLine("************0、退出管理程序************");
            Console.WriteLine("************1、随机分组****************");
            Console.WriteLine("************2、按院系分组**************");
            Console.WriteLine("************3、能力值分组**************");
            Console.WriteLine("************4、性别比例分组************");
        }
        //随机方法
        public void Random(Student [] s)
        {
            string[] arr = new string[201];
            string[] major = new string[201];
            int[] sex = new int[201];
            int[] ability = new int[201];
            int[] id = new int[201];
            int[] major1 = new int[201];
            for (int i = 0; i < 200; i++)
            {
                byte[] buffer = Guid.NewGuid().ToByteArray();
                int iSeed = BitConverter.ToInt32(buffer, 0);
                Random rm = new Random(iSeed);
                sex[i] = rm.Next(1, 3);
                ability[i] = rm.Next(3, 10);
                id[i] = i + 1000;
                major1[i] = rm.Next(1, 4);
                if (sex[i] == 1)
                {
                    arr[i] += $"{GetNameHelper.GetManName()}";
                }
                else
                {
                    arr[i] += $"{GetNameHelper.GetWomanName()}";
                }
                if (major1[i] == 1)
                {
                    major[i] = "计科";
                }
                else if (major1[i] == 2)
                {
                    major[i] = "信院";
                }
                else
                {
                    major[i] = "数院";
                }
                s[i] = new Student(id[i], arr[i], sex[i], ability[i], major[i]);
            }
        }
        //退出
        public void Quit()
        {
            Console.Clear();
            Console.WriteLine("退出成功，欢迎下次使用！");
            Console.ReadLine();
        }
        //打印随机分组并实现文件写入
        public void Write_group(Student [] s)
        {
            int p = 1;
            for (int i = 0; i < 200; i++)
            {
                if (i % 5 == 0)
                {
                    string text1 = $"第{p}组:";
                    Console.WriteLine(text1);
                    WriteAppend(text1);
                    p++;
                }
                string text2 = $"学生id: {s[i].Id}    学生姓名: {s[i].Name}   学生性别: {s[i].Sex}    学生能力: {s[i].Ability}    学生院系: {s[i].Major}";
                Console.WriteLine(text2);
                WriteAppend(text2);
            }
            Console.ReadLine();
        }
        //实现文件写入
        public static void WriteAppend(string text)
        {
            StreamWriter file = new StreamWriter("分组名单.txt", append: true);
            file.WriteLineAsync(text);
            file.Close();
        }

        //按专业分组
        public void Major_group(Student [] s)
        {
            int l = 0, k = 0, n = 0;
            Student[] s1 = new Student[200];
            Student[] s2 = new Student[200];
            Student[] s3 = new Student[200];
            //分三段赋值
            for (int j = 0; j < 200; j++)
            {
                if (s[j].Major == "计科")
                {
                    s1[l++] = s[j];
                    //s1[q] = new Student(id[q], arr[q], sex[q], ability[q], major[q]);
                }
                else if (s[j].Major == "信院")
                {
                    s2[k++] = s[j];
                    //s2[q] = new Student(id[q], arr[q], sex[q], ability[q], major[q]);
                }
                else
                {
                    s3[n++] = s[j];
                    //s1[q] = new Student(id[q], arr[q], sex[q], ability[q], major[q]);
                }
            }
            //后拼接
            for (int j = 0; j < k; j++)
                s1[l + j] = s2[j];
            for (int j = 0; j < n; j++)
                s1[l + k + j] = s3[j];
            Write_group(s1);
        }
        //按能力值分组
        public void Ability_group(Student [] s)
        {
            Student[] s0 = new Student[200];
            Student[] s1 = new Student[200];
            Student s_temp = new Student(0, "", 0, 0, "");
            for (int i = 0; i < 200; i++)
                s0[i] = s[i];
            //先排序
            for (int i = 0; i < 199; i++)
            {
                for (int j = 0; j < 199 - i; j++)
                {
                    if (s0[j].Ability < s0[j + 1].Ability)
                    {
                        s_temp = s0[j];
                        s0[j] = s0[j + 1];
                        s0[j + 1] = s_temp;
                    }
                }
            }
            //实现能力平均
            int l = 0;
            for (int i = 0; i < 40; i++)
                for (int j = 0; j < 200; j++)
                {
                    if (j % 40 == i)
                        s1[l++] = s0[j];
                }
            Write_group(s1);
        }
        //按性别分组
        public void Sex_group(Student [] s)
        {
            Student[] s0 = new Student[200];
            Student s_temp = new Student(0, "", 0, 0, "");
            for (int i = 0; i < 200; i++)
                s0[i] = s[i];
            //排序
            for (int i = 0; i < 199; i++)
            {
                for (int j = 0; j < 199 - i; j++)
                {
                    if (s0[j].Sex < s0[j + 1].Sex)
                    {
                        s_temp = s0[j];
                        s0[j] = s0[j + 1];
                        s0[j + 1] = s_temp;
                    }
                }
            }
            Write_group(s0);
        }
        //判断m调用不同方法
        public void Judgment(int m, Student [] s)
        {
            if (m == 1)
            {
                WriteAppend("随机分组名单:");
                Program program1 = new Program();
                program1.Write_group(s);
            }
            else if (m == 2)
            {
                WriteAppend("专业分组名单:");
                Program program2 = new Program();
                program2.Major_group(s);
            }
            else if (m == 3)
            {
                WriteAppend("能力分组名单:");
                Program program3 = new Program();
                program3.Ability_group(s);
            }
            else if (m == 4)
            {
                WriteAppend("性别分组名单:");
                Program program4 = new Program();
                program4.Sex_group(s);
            }
            else
                Console.WriteLine("ERROR");
        }
        //实现对分组情况的文件写入
        /*public void File_Write(Student [] s)
        {

        }*/
        //主程序
        static void Main(string[] args)
        {
            window();
            int m;
            Student[] s = new Student[201];         
            Program program = new Program();
            program.Random(s);                      //随机分组
            //循环实现，直至0时退出
            for (int i = 0; (m = Convert.ToInt32(Console.ReadLine())) != 0; i++)
            {               
                program.Judgment(m, s);                 //判断m调用不同方法
                window();
            }
            program.Quit();
        }
    }
}

