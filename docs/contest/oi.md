author: Ir1d, Planet6174, abc1763613206, StudyingFather, cjsoft, Marcythm, luoguyuntianming, ChungZH, Xeonacid, YZircon, i-Yirannn, H-J-Granger, NachtgeistW, YuzhenQin, Andycode3759, HHH2309, shigengxin123456, Re-Ori, hcx1204

## About the contests

The **Olympiad in Informatics** (OI) is a subject competition widely held among secondary school students, just like the physics and math olympiads. OI tests a contestant's ability to solve practical problems by writing computer programs, using algorithms, data structures and mathematics.

There are many OI contests. In China alone, they include:

-   National Olympiad in Informatics in Provinces (NOIP)
-   National Olympiad in Informatics (NOI)
-   NOI Winter Camp (WC)
-   China Team Selection Competition for the IOI (CTSC)

International OI contests include:

-   International Olympiad in Informatics (IOI)
-   USA Computing Olympiad (USACO)
-   Japanese Olympiad in Informatics (JOI)
-   Asia-Pacific Informatics Olympiad (APIO)

    ……

For most contestants, each new season starts with the first round of CSP-J/S in September.

In China, the only language allowed in OI contests is C++ (C and Pascal were allowed in the past, but support for both has ended). Different contests have different rules about the C++ version. Problems are usually about algorithms or data structures. Problem types include traditional problems (the most common kind, where input and output go through specified files) and non-traditional problems (output-only problems, interactive problems, code-completion problems, and so on).

## Contest formats

### OI format

Contestants get only one submission. They can't see judging results during the contest; scores are published after the contest. Each problem has several test cases, and you get points based on how many test cases you pass. Test cases may also give partial points, so you can score even if your program only works on part of the data.

???+ note "The selfEval self-testing tool"
    Nowadays some NOI-series contests provide the selfEval self-testing tool, which is built into the custom edition of NOI Linux used in national contests. It was officially announced and first used at NOI2023, and has since been used at later NOI national contests, APIO (China region), the NOI Winter Camp and others. Contestants can use selfEval to test their programs on a set of test data (called pretest data) and get feedback. There is a cap on the number of self-tests per contest (50 at NOI2024 and 30 at NOI2025), and the pretest data is not visible to contestants. Since the pretest data differs from the official test data, self-test results are only for debugging and do not count as official scores. Repeated pretests on the same problem use the same pretest data.

The second round of CSP-J/S, NOIP, the provincial team selection and NOI all use the OI format.

### IOI format

Contestants can submit many times during the contest. Submissions are judged in real time and results are returned. Wrong submissions carry no penalty. Each problem has several test cases, and you get points based on how many test cases you pass.

APIO and IOI both use the IOI format. Contests in China are also gradually moving toward the IOI format.

### Codeforces (CF) format

[Codeforces](https://codeforces.com) is an online judge that holds contests regularly.

What's special about its contests is that only part of the data (Pretests) is tested during the contest, and the full results on all test cases (System Tests) are returned after the contest ends. You can submit many times during the contest, and you may Hack other people's code (here, Hack means submitting a test case that makes someone else's code give a wrong answer). To Hack, you must lock your own code for that problem (in other words, you can't resubmit it for the rest of the contest). When hacking, you are not allowed to copy the other contestant's program to test it locally; the source code is shown as an image.

Codeforces also offers another format called Extended ICPC (or ICPC+). In this format, all data is tested during the contest, but after the contest there is a 12-hour open Hack phase for everyone. During this phase you may copy contestants' programs to test them locally.

## Major contests

### CSP-J/S

**CSP-J/S** (Certified Software Professional Junior/Senior) is a non-professional software skills certification test that the CCF set up after NOIP was cancelled in 2019. Before 2025 it was open to all ages; [later it was limited to those aged 12 and above](https://www.noi.cn/xw/2025-02-13/837984.shtml).

CSP-J/S has two groups: Junior (CSP-J) and Senior (CSP-S). There are two rounds: the first round (usually in September each year) and the second round (usually in October each year). The first round is a written test covering computer theory, general computer knowledge, and basic algorithms and math. The second round is a programming exam on computers. Both Junior and Senior have 4 problems; the Junior exam lasts 3.5 hours and the Senior exam 4 hours (except CSP-S 2019, which used the old NOIP Senior Group format: two days, 3 problems in 3.5 hours each day). Any student aged 12 or above can register for the first round, and the top performers after ranking get the chance to take part in the second round.

Registering for the first/second round and filing appeals about problems after the second round all require paying fees to the CCF.

Both rounds rank contestants within each province and certify them at first, second and third levels.

### NOIP

**NOIP** (National Olympiad in Informatics in Provinces) is an informatics contest organized in the People's Republic of China for secondary school students in China (including Hong Kong and Macau).

Old format, 2018 and earlier: NOIP was divided by participant level into the Junior Group and the Senior Group, and in 2018 an entry-level group was piloted in Shanghai. It was divided into two stages: the preliminary round and the final round. The preliminary round tested some basic computer knowledge and basic algorithms, and the final round was a programming exam on computers. It was usually held on the second weekend of November: Senior Group Day 1 on Saturday morning 8:30-12:00 (3.5 hours, 3 problems), the Junior Group on Saturday afternoon 14:30-18:00 (3.5 hours, 4 problems), and Senior Group Day 2 on Sunday morning 8:30-12:00 (3.5 hours, 3 problems). The whole country used the same problem set, but award rules were set uniformly by the CCF (China Computer Federation) based on each province's situation and were published after the contest on the [official NOI website](http://www.noi.cn). The cutoff for a first prize differed slightly between provinces.

NOIP was [suspended by the CCF](http://www.noi.cn/xw/2019-08-16/715365.shtml) on August 16, 2019, and [announced to be restored](http://www.noi.cn/xw/2020-01-21/715520.shtml) on January 21, 2020. Since 2020, the NOIP format has been different from before:

-   The preliminary round was dropped and replaced by the first round of CSP-J/S;
-   The Junior Group was dropped and replaced by CSP-J. Since then NOIP has had only one group, aimed at Senior-level contestants;
-   The schedule was cut from two days with 6 problems in total (3.5 hours each day) to one day with 4 problems in 4.5 hours.
-   Contestants need to reach a certain rank in the second round of CSP-S to qualify for NOIP; the exact quotas differ between provinces. A province's NOIP quota depends on factors such as its number of participants and results in the previous season.

Registering for NOIP and filing appeals about problems do not require extra fees.

NOIP awards are ranked within each province. As of 2019, at most universities, a provincial first prize in the Senior Group qualified a student for independent admission.

> In January 2020, the Ministry of Education of the People's Republic of China issued [Opinions on Piloting Admission Reform for Basic Disciplines at Some Universities](http://www.moe.gov.cn/srcsite/A15/moe_776/s3258/202001/t20200115_415589.html). It stated that from 2020, universities would no longer run independent admissions, and that some top universities would pilot an admission reform for basic disciplines (the Strong Foundation Plan).

### Provincial team selection

The **provincial team selection** (Shengxuan) selects each province's team for the national contest. It is usually held between January and April each year. It generally lasts two days, with 3 problems in 4.5 hours each day.

Each province decides its own selection problems; the current trend is for many provinces to set problems jointly.

The quota for each provincial team is computed by a complicated formula, usually related to past results and the number of participants. Usually, the NOIP score must make up a certain proportion of the selection score. According to the rules, junior high school students can only be selected as category E contestants and can't take part in the selection for categories A and B. Category A has 5 contestants ([at least 1 female](https://www.noi.cn/xw/2024-08-26/829152.shtml)), and the other contestants enter team B in order of their scores up to the given quota. The number of NOI places for one school can't exceed one third (rounded to the nearest integer) of the province's total A and B places; the highest-scoring female contestant who is selected for team A does not count toward this limit (this is called the 1/3 limit or 1/3 elimination; see the [CCF official explanation](https://www.noi.cn/xw/2022-12-14/781364.shtml) for details).

From 2020, the NOI provincial team selection problems were set and judged uniformly by the CCF. Provinces able to set problems could set their own, but their selection method needed CCF approval. From 2024, provinces went back to setting their own selection problems. Provinces that want to can hold joint exams or use other provinces' problems, but the specific plan needs CCF approval.

### NOI

**NOI** (National Olympiad in Informatics) is the highest-level contest for provincial teams in China, including Hong Kong and Macau.

NOI is usually held in July. Contestants are either official contestants or summer camp contestants. Official contestants are split into three categories: A and B are official members of provincial teams, and C are invitational contestants. Categories A and B match the A and B contestants of the provincial teams (category A gets a 5-point bonus when scores are calculated). Category C is, in name, a reward quota for schools that have made outstanding contributions to the CCF. Summer camp contestants are split into categories D and E, which are senior high and junior high students taking part as unofficial contestants. If a summer camp contestant scores above the cutoff, they only get a certificate of their score, not a medal (so the same score is worth somewhat less). The top 50 official contestants form the national training team and get guaranteed university admission.

On international platforms, it is sometimes called CNOI to tell it apart from other contests also called NOI.

### CTT

**CTT** (China Team Training) is the training and selection event held every winter for members of the IOI national training team. It consists of 3-4 tests. Besides the national training team, some contestants who did especially well at that year's NOI can also take part in CTT under the name "elite training".

CTT, together with homework and other parts, makes up the first stage of national team selection. Since 2021, the top 30 contestants in the first stage become national team candidates and move on to the second stage of selection (WC).

### WC

**WC** (Winter Camp, the NOI Winter Camp) is an event held every winter in the city that hosted that year's NOI. Although it is mainly for training the national training team and selecting the national team, contestants who did well at the previous year's NOIP and the second round of CSP-S can also attend as unofficial participants.

WC consists of several days of training and tests. The test scores are combined with scores from earlier stages to compute the overall ranking of the training team members. Before 2020, there was only one test, and the training team and unofficial participants took the same problems; the top 15 of the training team by overall score became national team candidates and took part in the final stage of selection (CTS, etc.). Since 2021, as the national team selection role of CTS was merged into WC, the candidates take two tests, while unofficial participants still take one, and some of the unofficial participants' problems overlap with the candidates' problems. The top 6 candidates by overall ranking go on to a final interview, from which 4 official contestants and 2 reserve contestants are chosen for that year's IOI.

### APIO

**APIO** (Asia-Pacific Informatics Olympiad) is an informatics competition for secondary school students in the Asia-Pacific region. Every year in early May, the CCF hosts a mirror contest for the China region. There are training activities around the contest day.

APIO contestants are split into categories A and B. The top six of category A (ties included) are eligible for APIO's international awards, while category B contestants can only receive China-region awards.

### CTS

**CTS** (formerly CTSC, China Team Selection Competition for the IOI) selects the national team (6 people) from the national team candidates (15 people) to compete at that summer's IOI: 4 official contestants and 2 reserves. As with WC, contestants who did well at the previous year's NOIP can also take part (but are not part of the selection).

Registration for APIO and CTS is done by province. The participants are usually decided by ranking NOIP scores (the two events are usually very close in time).

CTS 2020 was cancelled due to the pandemic, and that year's national team was selected through NOI. Since 2021, the CTS selection process has been replaced by WC.

### IOI

**IOI** (International Olympiad in Informatics) is an annual informatics competition for secondary school students around the world. Each country sends four contestants, and the contest is usually streamed live. In the IOI format, each problem has Subtasks, and each subtask is worth a certain number of points.

### University camps

#### Peking University (PKU)

-   Peking University Informatics Winter Camp (PKUWC): held around the time of the Winter Camp.
-   Peking University Informatics Camp (PKUSC): usually held on campus in June. Since the contest takes place in the university's computer labs, the environment is Windows and the contest system is OpenJudge.
-   Peking University Summer Classes for Secondary School Students (Informatics): held during the summer holiday, for science students in the second year of senior high school.

#### Tsinghua University (THU)

-   Department of Computer Science "High School–University Bridging" winter seminar and teaching event: similar to an informatics winter camp, sometimes abbreviated in English as THUWC. It usually lasts two days. Mornings are contests (day one is a standard OI contest, day two is Tsinghua's own "engineering problem" contest), and afternoons are training courses.

## OI contests in other countries and regions

### USA: USACO

Official website: <http://www.usaco.org/>

USACO is probably the foreign OI contest Chinese contestants know best (and probably also the one with the most editorials in Chinese).

From winter to early spring each year, USACO holds one online contest per month. Each contest lasts 3\~5 hours.

According to the official website, USACO contests are divided into these 4 levels (3 levels before the 2015\~2016 school year):

-   Bronze, for programming beginners, especially students who have only learned the most basic algorithms (such as sorting and binary search);
-   Silver, for students starting to learn basic algorithmic techniques (such as recursion, search and greedy algorithms) and basic data structures;
-   Gold, where students meet more complex algorithms (such as shortest paths and DP) and more advanced data structures;
-   Platinum, for contestants with solid algorithm design skills; Platinum challenges them with complex and more open-ended problems.

In China, Luogu is currently the OJ with the most complete collection of USACO problems.

### Poland: POI

Official website: <https://oi.edu.pl/>

Official submission site: <https://szkopul.edu.pl/p/default/problemset/>

POI is the foreign OI contest that many provincial-selection-level contestants practice on most.

According to the [POI official website](https://oi.edu.pl/l/42/), POI works as follows:

-   Round 1: six problems (five problems in the 31st edition and earlier), online contest;
-   Round 2: one practice contest and two official contests; the practice contest has one problem and each official contest has two;
-   Round 3: one practice contest and two official contests; the practice contest has one problem and each official contest has three.

In some years there was also a contest called ONTAK, officially the POI training camp, comparable to China's national training team training (CTT).

Poland also holds an open contest called PA, which roughly means "Algorithmic Engagements". Its official website is: <https://potyczki.mimuw.edu.pl/>.

Among Chinese OJs, BZOJ currently has the most complete collection of POI problems.

### Croatia: COCI

Official website (English): <http://www.hsin.hr/coci/>

Official website (Croatian): <http://www.hsin.hr/honi/>

The difficulty range is very wide, roughly from Junior-minus to provincial-selection-minus level.

In the past, COCI provided statements, test data, editorials and reference solutions for all problems. From the end of 2017, COCI stopped publishing editorials and reference solutions. Starting from the 2019-2020 season, they began publishing them again.

Luogu, BZOJ and LibreOJ all have a few COCI problems.

### Japan: JOI

Official website: <https://www.ioi-jp.org/>

JOI (Japanese Olympiad in Informatics) provides statements, test data, editorials and reference solutions for all problems. The JOI Final and Spring Camp of the past two years provide English statements but no English editorials. Every JOI Open so far has provided English statements and editorials.

How JOI works:

-   Preliminary round (Yosen)
-   Final round (Honsen/JOI Final)
-   Spring camp (Spring Training Camp/JOI Spring Camp/JOISC)
-   Open contest (correspondence course/JOI Open Contest)

The preliminary round is fairly easy, and since the 2019/2020 season it has been split into several rounds. JOI Final ranges from about Senior-minus to Senior-plus difficulty. JOISC and JOI Open problems range from Senior to NOI-minus difficulty.

Most JOI problems can be submitted on [AtCoder](https://atcoder.jp/). You can find more JOI problems (with Japanese statements) on the JOI official website or on AtCoder.

LibreOJ and BZOJ currently have problems from recent JOI Final, JOISC and JOI Open contests.

### Russia: ROI

Official website: <http://neerc.ifmo.ru/school/archive/index.html>

Online submission: <https://contest.yandex.ru/roiarchive/> and Codeforces (some problems).

ROI (Russian: олимпиадная информатика, Russian Olympiad in Informatics) is Russia's informatics olympiad.

Stages:

-   Municipal stage (Municipal Stage/Муниципальный этап)
-   Regional stage (Regional Stage/Региональный этап)
-   Final stage (Final Stage/Заключительный этап)

LibreOJ currently has translations of the ROI final problems from recent years.

Besides ROI, other large Russian contests for secondary school students include:

-   Internet Olympiads in Informatics (Russian: Интернет-олимпиады по информатике)
    -   Official website: <http://neerc.ifmo.ru/school/io/index.html>
    -   This contest is run by the ROI problem setters.
-   All-Russian Team Olympiad in Informatics for school students (Russian: Всероссийской командной олимпиады школьников)
    -   Official website: <http://neerc.ifmo.ru/school/russia-team/index.html>
    -   Its qualifying contest, the Moscow Team Olympiad, can be submitted on Codeforces.
-   Innopolis Open
    -   Official website <https://olymp.innopolis.ru/en/ooui/information/>
-   Open Olympiad in Programming for school students (Открытая олимпиада школьников по программированию)
    -   Official website: <https://olympiads.ru/zaoch/>
    -   The official website says this contest is on the same level as ROI.

### Canada: CCC & CCO

CCC (Canadian Computing Competition) and CCO (Canadian Computing Olympiad): you can find information and problems from past years on their [official website](https://cemc.math.uwaterloo.ca/contests/past_contests.html#ccc).

You can submit [CCC](https://dmoj.ca/problems/?category=4) and [CCO](https://dmoj.ca/problems/?category=24) problems on DMOJ, which also has editorials for CCC.

CCC Junior/Senior are close in difficulty to the NOIP Junior/Senior Groups. To win a gold medal at CCO you probably need NOI silver medal level.

### Singapore: NOI SG

Official website: <https://noisg.comp.nus.edu.sg/noi/>

Its full name is the Singapore National Olympiad in Informatics; within Singapore, where there is no ambiguity, it is also called NOI. It has an Online Qualification Contest and a Final Contest. Schools register for the online qualification contest, and contestants compete at their own school and submit remotely over the internet. Qualification results are only ranked within each school; the top 5 contestants with non-zero scores qualify to represent their school at the national final.

Chinese OJs currently have few NOI SG problems. You can find past statements, test data and official solutions on the [official GitHub account](https://github.com/noisg).

### Taiwan: Informatics Olympiad

In Taiwan, the "informatics" in OI is translated with a different Chinese word than the one commonly used in mainland China.

Contestants in Taiwan who want to go to the IOI need to go through these contests:

-   Regional Informatics Subject Competition
-   National Informatics Subject Competition
-   Informatics Training Camp (TOI)

### Other countries

-   Australia: AIO: <https://orac.amt.edu.au/hub/aio/>

    -   Difficulty similar to NOI.

-   UK: British Informatics Olympiad: <https://www.olympiad.org.uk/>

    -   Too easy.

-   Czech Republic: Matematická olympiáda–kategorie P: <http://mo.mff.cuni.cz/p/archiv.html>

-   Romania: Olimpiada Nationala de Informatica: <http://olimpiada.info/>
    -   Look for statements, test data and editorials in the tabs labeled Subiecte.

## Other international OI contests

### BalticOI

**BalticOI** is for the countries around the Baltic Sea. BalticOI 2018 had 9 participating countries, including Lithuania, Poland, Estonia and Finland. The problems are hard.

Except for 2017, BalticOI publishes statements, test data and editorials every year. BalticOI has no fixed official website; each year's host creates a new one. See this [post](https://loj.ac/article/416) for the official websites of past years.

LibreOJ currently has BalticOI problems from about the last ten years.

### BalkanOI

**BalkanOI** is for the countries around the Balkans. BalkanOI 2018 had 12 participating countries, including Romania, Greece, Bulgaria and Serbia. The problems are hard.

BalkanOI only published statements, test data and editorials in some years. See this [post](https://loj.ac/article/416) for the official websites.

### CEOI

The participating countries of CEOI 2018 partly overlap with the two contests above, including Poland, Romania, Georgia and Croatia. The problems are hard.

CEOI publishes statements, test data and editorials every year. See this [post](https://loj.ac/article/416) for the official websites.

### eJOI

**eJOI** stands for European Junior Olympiad in Informatics. Participating countries include Russia, Armenia, Bulgaria and Poland. The problems are fairly hard.

eJOI publishes statements, test data and editorials every year. See this [post](https://loj.ac/article/416) for the official websites.

### NOI

???+ warning "Warning"
    This is not China's "National Olympiad in Informatics".

**NOI** stands for Nordic Olympiads in Informatics.

Official website: <http://nordic.progolymp.se>

A contest that only started in the last couple of years, for the Nordic countries.

## References

-   [ICPC/CCPC contests and format](./icpc.md)
-   ["Translation Team" Websites of some continental OI contests](https://loj.ac/article/416)
