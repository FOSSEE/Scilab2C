/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008-2008 - INRIA - Allan SIMON
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#include "matrixInversion.h" 
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define LEADDIM 10

#define SMATRIX_IN {0.56672112690284848f,0.57116389367729425f,0.81601104838773608f,0.05689279362559319f,\
 0.55959366867318749f,0.12493403162807226f,0.72792222863063216f,0.26777664758265018f,\
 0.54653349192813039f,0.98854076582938433f,\
0.73956565884873271f,0.00371731072664261f,0.59005728596821427f,0.3096467358991504f,\
 0.25522057106718421f,0.62518793903291225f,0.11574173765257001f,0.61170040909200907f,\
 0.67839562846347690f,0.33200952783226967f,\
0.02587099233642220f,0.51744682248681784f,0.39168732380494475f,0.24135384149849415f,\
 0.50644348980858922f,0.42361020017415285f,0.28937275288626552f,0.08879321813583374f,\
 0.62128817522898316f,0.34549844544380903f,\
0.70648676296696067f,0.52114724926650524f,0.28704008506610990f,0.65027950797230005f,\
 0.08813347620889544f,0.44987633451819420f,0.72272530803456903f,0.89767962601035833f,\
 0.24278218811377883f,0.43377211131155491f,\
0.96770532103255391f,0.50685344357043505f,0.52329764096066356f,0.5596947595477104f,\
 0.56173070007935166f,0.46817600261420012f,0.77945467224344611f,0.79010718129575253f,\
 0.98085420625284314f,0.81870661024004221f,\
0.42568723810836673f,0.24615605548024178f,0.92295324662700295f,0.10007458087056875f,\
 0.46782181179150939f,0.39504976756870747f,0.03661171020939946f,0.51753685344010592f,\
 0.83254515705630183f,0.61048321425914764f,\
0.18711117887869477f,0.01895748358219862f,0.84335647663101554f,0.07485948316752911f,\
 0.85328151332214475f,0.01245901081711054f,0.18675393564626575f,0.49205840751528740f,\
 0.74896081397309899f,0.94149570073932409f,\
0.21240556007251143f,0.57950199581682682f,0.26281475694850087f,0.43609866220504045f,\
 0.91105451015755534f,0.80826673656702042f,0.81026530498638749f,0.25904283951967955f,\
 0.41390872886404395f,0.35999277792870998f,\
0.69127879338338971f,0.76568587962538004f,0.35726496530696750f,0.76933998242020607f,\
 0.54776339093223214f,0.09622887428849936f,0.95611717319115996f,0.22074085660278797f,\
 0.01432593585923314f,0.81914897728711367f,\
0.13049928424879909f,0.96820035576820374f,0.6561381467618048f,0.24455389659851789f,\
 0.52831235667690635f,0.84689256362617016f,0.78766220854595304f,0.12620826158672571f,\
 0.78838609857484698f,0.34530424699187279f}

#define SMATRIX_TEST {-0.52918209318099763f,-1.4122060840199684f,-2.81447731203224061f,-1.55267562705322471f,\
 1.7795249093271313f,3.41331242497436538f,-1.88904543501184552f,1.12197724430279377f,\
 0.72267367241531266f,-0.34793324767314804f,\
-0.04291642356311276f,-3.42251783874691506f,0.02468613395048536f,0.08908661449574046f,\
 0.97788374996171823f,4.61261377725807620f,-2.59399616857143833f,1.20317500146072143f,\
 -0.02166245003208622f,-1.3267013649317376f,\
-2.67087412768695565f,-0.22033432555244847f,-5.29579931307827412f,-1.14315667195430248f,\
 0.09168583909366912f,1.5851803683202144f,1.66558750370151065f,-0.86555486622239652f,\
 1.8195567574793376f,3.61754347340892135f,\
-1.89697408392725020f,1.8626200864938904f,0.79417407448685418f,-0.05121347333860876f,\
 -0.58894433303940863f,-2.25150397211694164f,1.83391219779456915f,-1.71612581802446540f,\
 1.573412079629398f,1.342726670155854f,\
-2.25362434223770558f,-3.27855988666729736f,-4.38426363396032048f,-1.74427000048068570f,\
 2.03129249683994884f,4.82780099711724908f,-0.73809777439724900f,2.2509436506925824f,\
 0.94584198058114821f,0.25243671945739055f,\
3.84378244490602494f,3.72355620392145159f,6.53582696174593814f,1.94952916234761564f,\
 -3.13395988068588593f,-4.02699662712894213f,-0.76253598522946087f,0.23575927310254180f,\
 -1.8359327702678865f,-2.83401823371425543f,\
-1.18180799907519307f,0.63788382527496235f,-3.78074265572599399f,-0.54137361290359209f,\
 0.70395890323932231f,-2.37398893454907611f,2.2701087812490388f,-0.86112335471809098f,\
 0.47829335155324559f,3.33447092282135671f,\
-0.74596393761410851f,-2.37451784604461391f,-1.71445760029220273f,1.04267932396181950f,\
 0.72418115460071419f,2.59078382027510390f,-0.24977554095572621f,1.00522161428916723f,\
 -0.63851725590828357f,-0.32538135452852734f,\
-1.03321944290699186f,0.06105622131119152f,-0.23434658474553238f,-0.78361018751135569f,\
 1.52101204019895975f,-0.98475391631291920f,0.82324943504312742f,-1.09543520381998416f,\
 -0.06310749918170644f,1.29987814669920709f,\
6.08715177443300171f,4.38684491456130132f,10.9588676689371631f,3.07570017972914656f,\
 -3.9362327692213568f,-6.43408376602510224f,-0.44360914322700107f,-0.86171558904483270f,\
 -2.44206676099519093f,-4.96806164188692279f}

#define DMATRIX_IN {0.56672112690284848,0.57116389367729425,0.81601104838773608,0.05689279362559319,\
 0.55959366867318749,0.12493403162807226,0.72792222863063216,0.26777664758265018,\
 0.54653349192813039,0.98854076582938433,\
0.73956565884873271,0.00371731072664261,0.59005728596821427,0.3096467358991504,\
 0.25522057106718421,0.62518793903291225,0.11574173765257001,0.61170040909200907,\
 0.67839562846347690,0.33200952783226967,\
0.02587099233642220,0.51744682248681784,0.39168732380494475,0.24135384149849415,\
 0.50644348980858922,0.42361020017415285,0.28937275288626552,0.08879321813583374,\
 0.62128817522898316,0.34549844544380903,\
0.70648676296696067,0.52114724926650524,0.28704008506610990,0.65027950797230005,\
 0.08813347620889544,0.44987633451819420,0.72272530803456903,0.89767962601035833,\
 0.24278218811377883,0.43377211131155491,\
0.96770532103255391,0.50685344357043505,0.52329764096066356,0.5596947595477104,\
 0.56173070007935166,0.46817600261420012,0.77945467224344611,0.79010718129575253,\
 0.98085420625284314,0.81870661024004221,\
0.42568723810836673,0.24615605548024178,0.92295324662700295,0.10007458087056875,\
 0.46782181179150939,0.39504976756870747,0.03661171020939946,0.51753685344010592,\
 0.83254515705630183,0.61048321425914764,\
0.18711117887869477,0.01895748358219862,0.84335647663101554,0.07485948316752911,\
 0.85328151332214475,0.01245901081711054,0.18675393564626575,0.49205840751528740,\
 0.74896081397309899,0.94149570073932409,\
0.21240556007251143,0.57950199581682682,0.26281475694850087,0.43609866220504045,\
 0.91105451015755534,0.80826673656702042,0.81026530498638749,0.25904283951967955,\
 0.41390872886404395,0.35999277792870998,\
0.69127879338338971,0.76568587962538004,0.35726496530696750,0.76933998242020607,\
 0.54776339093223214,0.09622887428849936,0.95611717319115996,0.22074085660278797,\
 0.01432593585923314,0.81914897728711367,\
0.13049928424879909,0.96820035576820374,0.6561381467618048,0.24455389659851789,\
 0.52831235667690635,0.84689256362617016,0.78766220854595304,0.12620826158672571,\
 0.78838609857484698,0.34530424699187279}

#define DMATRIX_TEST {-0.52918209318099763,-1.4122060840199684,-2.81447731203224061,-1.55267562705322471,\
 1.7795249093271313,3.41331242497436538,-1.88904543501184552,1.12197724430279377,\
 0.72267367241531266,-0.34793324767314804,\
-0.04291642356311276,-3.42251783874691506,0.02468613395048536,0.08908661449574046,\
 0.97788374996171823,4.61261377725807620,-2.59399616857143833,1.20317500146072143,\
 -0.02166245003208622,-1.3267013649317376,\
-2.67087412768695565,-0.22033432555244847,-5.29579931307827412,-1.14315667195430248,\
 0.09168583909366912,1.5851803683202144,1.66558750370151065,-0.86555486622239652,\
 1.8195567574793376,3.61754347340892135,\
-1.89697408392725020,1.8626200864938904,0.79417407448685418,-0.05121347333860876,\
 -0.58894433303940863,-2.25150397211694164,1.83391219779456915,-1.71612581802446540,\
 1.573412079629398,1.342726670155854,\
-2.25362434223770558,-3.27855988666729736,-4.38426363396032048,-1.74427000048068570,\
 2.03129249683994884,4.82780099711724908,-0.73809777439724900,2.2509436506925824,\
 0.94584198058114821,0.25243671945739055,\
3.84378244490602494,3.72355620392145159,6.53582696174593814,1.94952916234761564,\
 -3.13395988068588593,-4.02699662712894213,-0.76253598522946087,0.23575927310254180,\
 -1.8359327702678865,-2.83401823371425543,\
-1.18180799907519307,0.63788382527496235,-3.78074265572599399,-0.54137361290359209,\
 0.70395890323932231,-2.37398893454907611,2.2701087812490388,-0.86112335471809098,\
 0.47829335155324559,3.33447092282135671,\
-0.74596393761410851,-2.37451784604461391,-1.71445760029220273,1.04267932396181950,\
 0.72418115460071419,2.59078382027510390,-0.24977554095572621,1.00522161428916723,\
 -0.63851725590828357,-0.32538135452852734,\
-1.03321944290699186,0.06105622131119152,-0.23434658474553238,-0.78361018751135569,\
 1.52101204019895975,-0.98475391631291920,0.82324943504312742,-1.09543520381998416,\
 -0.06310749918170644,1.29987814669920709,\
6.08715177443300171,4.38684491456130132,10.9588676689371631,3.07570017972914656,\
 -3.9362327692213568,-6.43408376602510224,-0.44360914322700107,-0.86171558904483270,\
 -2.44206676099519093,-4.96806164188692279}

#define CRMATRIX_IN {0.56672112690284848f,0.57116389367729425f,0.81601104838773608f,0.05689279362559319f,\
 0.55959366867318749f,0.12493403162807226f,0.72792222863063216f,0.26777664758265018f,\
 0.54653349192813039f,0.98854076582938433f,\
0.73956565884873271f,0.00371731072664261f,0.59005728596821427f,0.3096467358991504f,\
 0.25522057106718421f,0.62518793903291225f,0.11574173765257001f,0.61170040909200907f,\
 0.67839562846347690f,0.33200952783226967f,\
0.02587099233642220f,0.51744682248681784f,0.39168732380494475f,0.24135384149849415f,\
 0.50644348980858922f,0.42361020017415285f,0.28937275288626552f,0.08879321813583374f,\
 0.62128817522898316f,0.34549844544380903f,\
0.70648676296696067f,0.52114724926650524f,0.28704008506610990f,0.65027950797230005f,\
 0.08813347620889544f,0.44987633451819420f,0.72272530803456903f,0.89767962601035833f,\
 0.24278218811377883f,0.43377211131155491f,\
0.96770532103255391f,0.50685344357043505f,0.52329764096066356f,0.5596947595477104f,\
 0.56173070007935166f,0.46817600261420012f,0.77945467224344611f,0.79010718129575253f,\
 0.98085420625284314f,0.81870661024004221f,\
0.42568723810836673f,0.24615605548024178f,0.92295324662700295f,0.10007458087056875f,\
 0.46782181179150939f,0.39504976756870747f,0.03661171020939946f,0.51753685344010592f,\
 0.83254515705630183f,0.61048321425914764f,\
0.18711117887869477f,0.01895748358219862f,0.84335647663101554f,0.07485948316752911f,\
 0.85328151332214475f,0.01245901081711054f,0.18675393564626575f,0.49205840751528740f,\
 0.74896081397309899f,0.94149570073932409f,\
0.21240556007251143f,0.57950199581682682f,0.26281475694850087f,0.43609866220504045f,\
 0.91105451015755534f,0.80826673656702042f,0.81026530498638749f,0.25904283951967955f,\
 0.41390872886404395f,0.35999277792870998f,\
0.69127879338338971f,0.76568587962538004f,0.35726496530696750f,0.76933998242020607f,\
 0.54776339093223214f,0.09622887428849936f,0.95611717319115996f,0.22074085660278797f,\
 0.01432593585923314f,0.81914897728711367f,\
0.13049928424879909f,0.96820035576820374f,0.6561381467618048f,0.24455389659851789f,\
 0.52831235667690635f,0.84689256362617016f,0.78766220854595304f,0.12620826158672571f,\
 0.78838609857484698f,0.34530424699187279f}

#define CIMATRIX_IN {0.26598573336377740f,0.12025266280397773f,0.90711546363309026f,0.41329363686963916f,\
 0.33616027468815446f,0.20337020372971892f,0.31845858739688993f,0.04173615900799632f,\
 0.00291663268581033f,0.92589621385559440f,\
0.97098186518996954f,0.82874121330678463f,0.33601493109017611f,0.14022908732295036f,\
 0.53368766140192747f,0.30119446106255054f,0.57618944440037012f,0.34382718056440353f,\
 0.89934705849736929f,0.09938172809779644f,\
0.88752476638182998f,0.31610729591920972f,0.11756130633875728f,0.49523561308160424f,\
 0.20390639593824744f,0.27625959040597081f,0.42549022240564227f,0.1970167332328856f,\
 0.83879271661862731f,0.42805786477401853f,\
0.20667528547346592f,0.53051907662302256f,0.92537237703800201f,0.41948772873729467f,\
 0.15899897180497646f,0.29445307422429323f,0.97619816288352013f,0.21228986512869596f,\
 0.43437494523823261f,0.94318309519439936f,\
0.85251609655097127f,0.57151748193427920f,0.72636712575331330f,0.86262222891673446f,\
 0.01818151073530316f,0.57180739520117640f,0.25189600000157952f,0.31403985014185309f,\
 0.77678761305287480f,0.03273952705785632f,\
0.67446978110820055f,0.04780154302716255f,0.90094979386776686f,0.28575096465647221f,\
 0.40983706060796976f,0.21417701244354248f,0.43911290075629950f,0.78216253779828548f,\
 0.13953176606446505f,0.92132670804858208f,\
0.91528743831440806f,0.82486197212710977f,0.39489932497963309f,0.25121363671496511f,\
 0.01058345986530185f,0.68954616272822022f,0.07593036955222487f,0.05409323470667005f,\
 0.11506372271105647f,0.94490244099870324f,\
0.02848597615957260f,0.5798843121156096f,0.56551797501742840f,0.33891015965491533f,\
 0.19653097167611122f,0.58555728476494551f,0.25593801774084568f,0.91902069095522165f,\
 0.53554199635982513f,0.900706990621984f,\
0.23678414756432176f,0.27918082987889647f,0.70614896761253476f,0.39219759730622172f,\
 0.27255953708663583f,0.42041230341419578f,0.06706167431548238f,0.46035157097503543f,\
 0.43117330456152558f,0.80943161016330123f,\
0.70153435599058867f,0.95451109297573566f,0.67878311965614557f,0.46815521270036697f,\
 0.34376550372689962f,0.42775720171630383f,0.76511315722018480f,0.29926850274205208f,\
 0.61453847866505384f,0.02519542910158634f} 

#define CRMATRIX_RESULT {1.13334136062879454f,1.00204710284162091f,-0.36268445209785111f,0.44135219666801256f,\
 -0.28889550886983612f,-0.83933700493692454f,0.02619582683916769f,-0.03686600548096228f,\
 -0.3105979269805872f,-0.41314497983816856f,\
-1.35807279244359291f,-0.95351719301170645f,0.24508427491574258f,-0.29038757219777517f,\
 0.37390577835866062f,1.1835902691419622f,-0.05725271188164360f,-0.45507733751420543f,\
 0.89349083196709700f,0.22599186865989143f,\
0.04475841273073522f,0.65452526617183937f,-0.45264724847008608f,1.48730985056287901f,\
 -0.62424039568072809f,-0.07013705727696817f,0.66279285096827567f,-0.49314454581179629f,\
 -0.75846179749076570f,0.03847068162421585f,\
-0.28834686632766587f,-0.12621821344664338f,0.66167042153468991f,-0.30750952923310820f,\
 -0.38799028698820520f,-0.06244610332663336f,-0.16699468178690519f,-0.25703548004808097f,\
 1.05027930016160997f,0.31201179786307248f,\
3.09851038226275932f,0.68543010150986716f,0.67201299485007393f,-1.36595464827487545f,\
 -0.97056467795873491f,-2.43637154663396904f,-0.44698290573897426f,0.25335968244039719f,\
 0.52656196888052886f,0.8186504936893056f,\
1.61532430192389009f,0.61052036715893920f,0.37049911672435160f,-0.89240571480272601f,\
 -0.10120030002332725f,-0.89781867625900547f,-0.69692694811392220f,1.15675538992405480f,\
 -0.60391534256305657f,-0.22021828342698485f,\
-0.3741129583278592f,-0.04777966095669883f,-0.71234429260192467f,0.67967568250401755f,\
 0.25551727122371526f,-0.21501817490214456f,0.33990052672394827f,0.26217278721004078f,\
 -0.62229775428125067f,0.12867275098729825f,\
-1.29410590757942501f,-0.90500447621878899f,-0.02669409932542677f,-0.65737384875432148f,\
 1.06680350537307067f,1.0309312701659521f,-0.17448425396711695f,0.10358425160515741f,\
 0.48518012284543799f,-0.12380980760248197f,\
-1.74148559631895505f,-0.80563620794306168f,0.09831541569063014f,0.29858001971458137f,\
 0.71315790168444038f,1.51589578494898358f,0.26752178758245609f,-0.07814488857312252f,\
 -0.33226019516643074f,-0.25594588429781640f,\
-0.55157638336116810f,-0.32553554473562663f,0.18945085905693287f,-0.49018398019943904f,\
 0.22032383413091419f,0.80929284051108974f,-0.26930477901947342f,0.01565276572275408f,\
 0.50897245662655299f,-0.2000796589321248f}

#define CIMATRIX_RESULT {-0.72071682835421724f,-0.27956750077582515f,-0.12213482023956473f,0.66199681493358187f,\
 0.19294748584842841f,0.71511499705121806f,-0.07262892107788382f,0.16934235088255833f,\
 -0.28481834522168847f,-0.4356262417043216f,\
0.89322305892893428f,-0.47480723687179577f,0.74313808566553685f,-0.47801173363000360f,\
 0.13877492668810687f,-0.24397029588270253f,-0.56410605487977428f,0.13174383488792796f,\
 -0.11275208753659083f,-0.02853860897251614f,\
-2.35574562422712885f,-0.66252937112300103f,0.41163350762074485f,0.21189678704881354f,\
 0.57210153384651341f,1.59871861336304111f,0.24013928122080053f,0.1908634439410304f,\
 0.04233444329438218f,-0.74974593479018292f,\
0.21852271998327827f,0.46641793006923571f,-0.50775725878230649f,0.36932403849454087f,\
 -0.97035140329820424f,-0.59905481375287661f,0.47057866052210873f,-0.27484558236611223f,\
 0.14983776443256616f,0.65314738162484509f,\
1.21784046668363755f,0.89544041489161419f,-0.55385999040744260f,2.3960585010456512f,\
 -1.08813967734866801f,-1.76566044616615891f,1.01831164014477937f,-0.39749297613335716f,\
 -1.42421433146953369f,0.1681331405197976f,\
1.2139424005771302f,1.25657353572343178f,-0.00767306183273730f,0.23949549471191356f,\
 -0.93651648982768132f,-0.892557290343648f,-0.31803824197434533f,-0.30269705651930523f,\
 0.06480270543120303f,0.04863444130781940f,\
-0.4833117651305104f,0.0427206592410736f,-0.32334126501314669f,-0.77563551313076551f,\
 0.77531171370204577f,0.4186703610529936f,0.06140053814127502f,0.40102788900264252f,\
 0.23384530409440230f,-0.64994440926481989f,\
1.96328712223105617f,0.26113952707794202f,0.7924550400337056f,-0.65512478202793500f,\
 -0.18012047754401772f,-1.54644464183129848f,-0.24103692367484025f,0.06994604293168416f,\
 -0.14071021436989639f,0.02396061029170871f,\
-0.38634718234016863f,-0.79360643330422442f,-0.24953759611467596f,-1.18124389108964234f,\
 0.36517943778230522f,0.69540420551183901f,-0.15267947346137922f,0.23673803504827576f,\
 0.58370191145957184f,0.41325242999322420f,\
0.27463944706760368f,-0.07374243215114486f,-0.23939703640616677f,-0.68898202198243763f,\
 0.18544512532830235f,-0.26697093307764330f,-0.38327334858322648f,-0.29893133575699177f,\
 0.40729781218472505f,0.82660964787147106f}



#define ZRMATRIX_IN {0.56672112690284848,0.57116389367729425,0.81601104838773608,0.05689279362559319,\
 0.55959366867318749,0.12493403162807226,0.72792222863063216,0.26777664758265018,\
 0.54653349192813039,0.98854076582938433,\
0.73956565884873271,0.00371731072664261,0.59005728596821427,0.3096467358991504,\
 0.25522057106718421,0.62518793903291225,0.11574173765257001,0.61170040909200907,\
 0.67839562846347690,0.33200952783226967,\
0.02587099233642220,0.51744682248681784,0.39168732380494475,0.24135384149849415,\
 0.50644348980858922,0.42361020017415285,0.28937275288626552,0.08879321813583374,\
 0.62128817522898316,0.34549844544380903,\
0.70648676296696067,0.52114724926650524,0.28704008506610990,0.65027950797230005,\
 0.08813347620889544,0.44987633451819420,0.72272530803456903,0.89767962601035833,\
 0.24278218811377883,0.43377211131155491,\
0.96770532103255391,0.50685344357043505,0.52329764096066356,0.5596947595477104,\
 0.56173070007935166,0.46817600261420012,0.77945467224344611,0.79010718129575253,\
 0.98085420625284314,0.81870661024004221,\
0.42568723810836673,0.24615605548024178,0.92295324662700295,0.10007458087056875,\
 0.46782181179150939,0.39504976756870747,0.03661171020939946,0.51753685344010592,\
 0.83254515705630183,0.61048321425914764,\
0.18711117887869477,0.01895748358219862,0.84335647663101554,0.07485948316752911,\
 0.85328151332214475,0.01245901081711054,0.18675393564626575,0.49205840751528740,\
 0.74896081397309899,0.94149570073932409,\
0.21240556007251143,0.57950199581682682,0.26281475694850087,0.43609866220504045,\
 0.91105451015755534,0.80826673656702042,0.81026530498638749,0.25904283951967955,\
 0.41390872886404395,0.35999277792870998,\
0.69127879338338971,0.76568587962538004,0.35726496530696750,0.76933998242020607,\
 0.54776339093223214,0.09622887428849936,0.95611717319115996,0.22074085660278797,\
 0.01432593585923314,0.81914897728711367,\
0.13049928424879909,0.96820035576820374,0.6561381467618048,0.24455389659851789,\
 0.52831235667690635,0.84689256362617016,0.78766220854595304,0.12620826158672571,\
 0.78838609857484698,0.34530424699187279}

#define ZIMATRIX_IN {0.26598573336377740,0.12025266280397773,0.90711546363309026,0.41329363686963916,\
 0.33616027468815446,0.20337020372971892,0.31845858739688993,0.04173615900799632,\
 0.00291663268581033,0.92589621385559440,\
0.97098186518996954,0.82874121330678463,0.33601493109017611,0.14022908732295036,\
 0.53368766140192747,0.30119446106255054,0.57618944440037012,0.34382718056440353,\
 0.89934705849736929,0.09938172809779644,\
0.88752476638182998,0.31610729591920972,0.11756130633875728,0.49523561308160424,\
 0.20390639593824744,0.27625959040597081,0.42549022240564227,0.1970167332328856,\
 0.83879271661862731,0.42805786477401853,\
0.20667528547346592,0.53051907662302256,0.92537237703800201,0.41948772873729467,\
 0.15899897180497646,0.29445307422429323,0.97619816288352013,0.21228986512869596,\
 0.43437494523823261,0.94318309519439936,\
0.85251609655097127,0.57151748193427920,0.72636712575331330,0.86262222891673446,\
 0.01818151073530316,0.57180739520117640,0.25189600000157952,0.31403985014185309,\
 0.77678761305287480,0.03273952705785632,\
0.67446978110820055,0.04780154302716255,0.90094979386776686,0.28575096465647221,\
 0.40983706060796976,0.21417701244354248,0.43911290075629950,0.78216253779828548,\
 0.13953176606446505,0.92132670804858208,\
0.91528743831440806,0.82486197212710977,0.39489932497963309,0.25121363671496511,\
 0.01058345986530185,0.68954616272822022,0.07593036955222487,0.05409323470667005,\
 0.11506372271105647,0.94490244099870324,\
0.02848597615957260,0.5798843121156096,0.56551797501742840,0.33891015965491533,\
 0.19653097167611122,0.58555728476494551,0.25593801774084568,0.91902069095522165,\
 0.53554199635982513,0.900706990621984,\
0.23678414756432176,0.27918082987889647,0.70614896761253476,0.39219759730622172,\
 0.27255953708663583,0.42041230341419578,0.06706167431548238,0.46035157097503543,\
 0.43117330456152558,0.80943161016330123,\
0.70153435599058867,0.95451109297573566,0.67878311965614557,0.46815521270036697,\
 0.34376550372689962,0.42775720171630383,0.76511315722018480,0.29926850274205208,\
 0.61453847866505384,0.02519542910158634} 

#define ZRMATRIX_RESULT {1.13334136062879454,1.00204710284162091,-0.36268445209785111,0.44135219666801256,\
 -0.28889550886983612,-0.83933700493692454,0.02619582683916769,-0.03686600548096228,\
 -0.3105979269805872,-0.41314497983816856,\
-1.35807279244359291,-0.95351719301170645,0.24508427491574258,-0.29038757219777517,\
 0.37390577835866062,1.1835902691419622,-0.05725271188164360,-0.45507733751420543,\
 0.89349083196709700,0.22599186865989143,\
0.04475841273073522,0.65452526617183937,-0.45264724847008608,1.48730985056287901,\
 -0.62424039568072809,-0.07013705727696817,0.66279285096827567,-0.49314454581179629,\
 -0.75846179749076570,0.03847068162421585,\
-0.28834686632766587,-0.12621821344664338,0.66167042153468991,-0.30750952923310820,\
 -0.38799028698820520,-0.06244610332663336,-0.16699468178690519,-0.25703548004808097,\
 1.05027930016160997,0.31201179786307248,\
3.09851038226275932,0.68543010150986716,0.67201299485007393,-1.36595464827487545,\
 -0.97056467795873491,-2.43637154663396904,-0.44698290573897426,0.25335968244039719,\
 0.52656196888052886,0.8186504936893056,\
1.61532430192389009,0.61052036715893920,0.37049911672435160,-0.89240571480272601,\
 -0.10120030002332725,-0.89781867625900547,-0.69692694811392220,1.15675538992405480,\
 -0.60391534256305657,-0.22021828342698485,\
-0.3741129583278592,-0.04777966095669883,-0.71234429260192467,0.67967568250401755,\
 0.25551727122371526,-0.21501817490214456,0.33990052672394827,0.26217278721004078,\
 -0.62229775428125067,0.12867275098729825,\
-1.29410590757942501,-0.90500447621878899,-0.02669409932542677,-0.65737384875432148,\
 1.06680350537307067,1.0309312701659521,-0.17448425396711695,0.10358425160515741,\
 0.48518012284543799,-0.12380980760248197,\
-1.74148559631895505,-0.80563620794306168,0.09831541569063014,0.29858001971458137,\
 0.71315790168444038,1.51589578494898358,0.26752178758245609,-0.07814488857312252,\
 -0.33226019516643074,-0.25594588429781640,\
-0.55157638336116810,-0.32553554473562663,0.18945085905693287,-0.49018398019943904,\
 0.22032383413091419,0.80929284051108974,-0.26930477901947342,0.01565276572275408,\
 0.50897245662655299,-0.2000796589321248}

#define ZIMATRIX_RESULT {-0.72071682835421724,-0.27956750077582515,-0.12213482023956473,0.66199681493358187,\
 0.19294748584842841,0.71511499705121806,-0.07262892107788382,0.16934235088255833,\
 -0.28481834522168847,-0.4356262417043216,\
0.89322305892893428,-0.47480723687179577,0.74313808566553685,-0.47801173363000360,\
 0.13877492668810687,-0.24397029588270253,-0.56410605487977428,0.13174383488792796,\
 -0.11275208753659083,-0.02853860897251614,\
-2.35574562422712885,-0.66252937112300103,0.41163350762074485,0.21189678704881354,\
 0.57210153384651341,1.59871861336304111,0.24013928122080053,0.1908634439410304,\
 0.04233444329438218,-0.74974593479018292,\
0.21852271998327827,0.46641793006923571,-0.50775725878230649,0.36932403849454087,\
 -0.97035140329820424,-0.59905481375287661,0.47057866052210873,-0.27484558236611223,\
 0.14983776443256616,0.65314738162484509,\
1.21784046668363755,0.89544041489161419,-0.55385999040744260,2.3960585010456512,\
 -1.08813967734866801,-1.76566044616615891,1.01831164014477937,-0.39749297613335716,\
 -1.42421433146953369,0.1681331405197976,\
1.2139424005771302,1.25657353572343178,-0.00767306183273730,0.23949549471191356,\
 -0.93651648982768132,-0.892557290343648,-0.31803824197434533,-0.30269705651930523,\
 0.06480270543120303,0.04863444130781940,\
-0.4833117651305104,0.0427206592410736,-0.32334126501314669,-0.77563551313076551,\
 0.77531171370204577,0.4186703610529936,0.06140053814127502,0.40102788900264252,\
 0.23384530409440230,-0.64994440926481989,\
1.96328712223105617,0.26113952707794202,0.7924550400337056,-0.65512478202793500,\
 -0.18012047754401772,-1.54644464183129848,-0.24103692367484025,0.06994604293168416,\
 -0.14071021436989639,0.02396061029170871,\
-0.38634718234016863,-0.79360643330422442,-0.24953759611467596,-1.18124389108964234,\
 0.36517943778230522,0.69540420551183901,-0.15267947346137922,0.23673803504827576,\
 0.58370191145957184,0.41325242999322420,\
0.27463944706760368,-0.07374243215114486,-0.23939703640616677,-0.68898202198243763,\
 0.18544512532830235,-0.26697093307764330,-0.38327334858322648,-0.29893133575699177,\
 0.40729781218472505,0.82660964787147106}


static void sinvermaTest (void)
{
   int i ; 
    
   float in[] = SMATRIX_IN ;
   
   float result[] = SMATRIX_TEST ;
   
   float out[LEADDIM*LEADDIM];
        
        
   sinverma (in, out, LEADDIM);
   
  	for ( i = 0 ; i < LEADDIM*LEADDIM  ; i++ )
	{

		printf ( "\t\t %d out : %e\tresult : %e\tassert : %e \n" , i , out[i] , result[i] , fabs ( out[i] - result[i] ) / fabs( out[i]) ) ;
		assert ( fabs ( out[i] - result[i] ) / fabs( out[i]) < 3e-6 ) ;
	} 
    
    
    
}

static void dinvermaTest (void)
{
   int i ; 
    
   double in[] = DMATRIX_IN ;
   
   double result[] = DMATRIX_TEST ;
   
   double out[LEADDIM*LEADDIM];
        
        
   dinverma (in, out, LEADDIM);
   
  	for ( i = 0 ; i < LEADDIM*LEADDIM  ; i++ )
	{

		printf ( "\t\t %d out : %e\tresult : %e\tassert : %e \n" , i , out[i] , result[i] , fabs ( out[i] - result[i] ) / fabs( out[i]) ) ;
		assert ( fabs ( out[i] - result[i] ) / fabs( out[i]) < 3e-16 ) ;
	} 
    
    
    
}

static void cinvermaTest (void)
{    
    int i = 0 ; 
    
    float tRealIn [] = CRMATRIX_IN ;
    float tImagIn [] = CIMATRIX_IN ;
    

        
    float tRealResult [] = CRMATRIX_RESULT ;
    float tImagResult [] = CIMATRIX_RESULT ;
    
    floatComplex  out[LEADDIM*LEADDIM ] ;
    
    floatComplex* in       = FloatComplexMatrix ( tRealIn , tImagIn , LEADDIM*LEADDIM );    
    floatComplex* Result   = FloatComplexMatrix ( tRealResult , tImagResult ,LEADDIM*LEADDIM) ;
    
    
    cinverma( in ,out , LEADDIM ) ;
    
    
        /* if we don't add that test assert failed if result = 0  'cause then we have  |(out - 0)|/|out| = 1*/     
	for ( i = 0 ; i < (LEADDIM*LEADDIM )  ; i++ )
	{
	  printf ( "\t\t %d out : %e\t %e\t * i  result : %e\t +%e\t * i  assert : %e + %e \n" ,
              i ,creals(out[i]) , cimags(out[i]) , creals (Result[i])  , cimags (Result[i]),
              fabs(  creals(out[i]) -  creals (Result[i]) ) / fabs (creals (out[i])) ,
              fabs(  cimags(out[i]) -  cimags (Result[i]) ) / fabs (cimags (out[i])));
           
    if (  creals(out[i])  < 1e-6 && creals (Result[i]) < 1e-6 )
        assert ( 1 ) ;
    else         
        assert ( fabs(  creals(out[i]) -  creals (Result[i]) ) / fabs (creals (out[i]))  < 3e-6 );
    
        
    if (  cimags(out[i])  < 1e-6 && cimags (Result[i]) < 1e-6 )
        assert ( 1 ) ;
    else         
	    assert ( fabs(  cimags(out[i]) -  cimags (Result[i]) ) / fabs (cimags (out[i]))  < 3e-6 ) ;
    
    }
}


static void zinvermaTest (void)
{    
    int i = 0 ; 
    
    double tRealIn [] = ZRMATRIX_IN ;
    double tImagIn [] = ZIMATRIX_IN ;
    

        
    double tRealResult [] = ZRMATRIX_RESULT ;
    double tImagResult [] = ZIMATRIX_RESULT ;
    
    doubleComplex  out[LEADDIM*LEADDIM ] ;
    
    doubleComplex* in       = DoubleComplexMatrix ( tRealIn , tImagIn , LEADDIM*LEADDIM );    
    doubleComplex* Result   = DoubleComplexMatrix ( tRealResult , tImagResult ,LEADDIM*LEADDIM) ;
    
    
    zinverma( in ,out , LEADDIM ) ;
    
    
        /* if we don't add that test assert failed if result = 0  'cause then we have  |(out - 0)|/|out| = 1*/     
	for ( i = 0 ; i < (LEADDIM*LEADDIM )  ; i++ )
	{
	  printf ( "\t\t %d out : %e\t %e\t * i  result : %e\t +%e\t * i  assert : %e + %e \n" ,
              i ,zreals(out[i]) , zimags(out[i]) , zreals (Result[i])  , zimags (Result[i]),
              fabs(  zreals(out[i]) -  zreals (Result[i]) ) / fabs (zreals (out[i])) ,
              fabs(  zimags(out[i]) -  zimags (Result[i]) ) / fabs (zimags (out[i])));
           
    if (  zreals(out[i])  < 1e-14 && zreals (Result[i]) < 1e-18 )
        assert ( 1 ) ;
    else         
        assert ( fabs(  zreals(out[i]) -  zreals (Result[i]) ) / fabs (zreals (out[i]))  < 3e-16 );
    
        
    if (  zimags(out[i])  < 1e-14 && zimags (Result[i]) < 1e-18 )
        assert ( 1 ) ;
    else         
	    assert ( fabs(  zimags(out[i]) -  zimags (Result[i]) ) / fabs (zimags (out[i]))  < 3e-16 ) ;
    
    }
}


static int testMatrixInversion(void) {

  printf("\n>>>> Matrix Inversion Tests\n");
  printf("\t>>>> Matrix Double Realt Tests\n");  
  dinvermaTest();

  printf("\n\n\t>>>> Matrix Float Realt Tests\n");     
  sinvermaTest();
  
  printf("\n\n\n");
  printf("\t>>>> Matrix Float Complex Tests\n");      
  cinvermaTest();  
    
  printf("\n\n\n");
  printf("\t>>>> Matrix Double Complex Tests\n");  
  zinvermaTest();

  return 0;
}



int main(void) {

  assert(testMatrixInversion() == 0);
  return 0;
}
