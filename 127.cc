#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "benchmark/benchmark.h"
#include "gtest/gtest.h"

using namespace std;

class BFS {
 public:
  BFS(const vector<string>& words, bool bidirectional)
      : words_(words), bidirectional_(bidirectional) {
    int n = words.size();
    for (int x = 0; x < n; x++) {
      string pattern = words[x];
      for (size_t i = 0, e = words[x].length(); i != e; ++i) {
        pattern[i] = '*';
        pattern_words_[pattern].push_back(x);
        pattern[i] = words[x][i];
      }
    }

    vector<string> singleton_patterns;
    for (const auto& entry : pattern_words_) {
      if (entry.second.size() == 1) {
        singleton_patterns.push_back(entry.first);
      }
    }
    for (const string& singleton_pattern : singleton_patterns) {
      pattern_words_.erase(singleton_pattern);
    }
  }

  int Search(const string& begin, const string& end) {
    if (bidirectional_) {
      return BidirectionalSearch(begin, end);
    } else {
      return UnidirectionalSearch(begin, end);
    }
  }

 private:
  int UnidirectionalSearch(const string& begin, const string& end) {
    int n = words_.size();
    queue<int> q;
    vector<int> steps(n, -1);

    int begin_id = find(words_.begin(), words_.end(), begin) - words_.begin();
    q.push(begin_id);
    steps[begin_id] = 1;

    while (!q.empty()) {
      int x = q.front();
      q.pop();
      if (words_[x] == end) {
        return steps[x];
      }
      for (int y : FindNeighbors(x)) {
        if (steps[y] == -1) {
          q.push(y);
          steps[y] = steps[x] + 1;
        }
      }
    }
    return 0;
  }

  int BidirectionalSearch(const string& begin, const string& end) {
    int n = words_.size();
    queue<int> q_forward;
    queue<int> q_backward;
    vector<int> steps_forward(n, -1);
    vector<int> steps_backward(n, -1);

    int begin_id = find(words_.begin(), words_.end(), begin) - words_.begin();
    int end_id = find(words_.begin(), words_.end(), end) - words_.begin();
    if (end_id == n) {
      return 0;
    }

    q_forward.push(begin_id);
    steps_forward[begin_id] = 0;
    q_backward.push(end_id);
    steps_backward[end_id] = 0;

    while (!q_forward.empty() && !q_backward.empty()) {
      int step = ExpandOneLevel(&q_forward, &steps_forward, steps_backward);
      if (step > 0) {
        return step;
      }
      step = ExpandOneLevel(&q_backward, &steps_backward, steps_forward);
      if (step > 0) {
        return step;
      }
    }
    return 0;
  }

  int ExpandOneLevel(queue<int>* q, vector<int>* steps,
                     const vector<int>& other_steps) {
    int q_size = q->size();
    for (int i = 0; i < q_size; i++) {
      int x = q->front();
      q->pop();
      for (int y : FindNeighbors(x)) {
        if ((*steps)[y] == -1) {
          q->push(y);
          (*steps)[y] = (*steps)[x] + 1;
          if (other_steps[y] >= 0) {
            return (*steps)[y] + other_steps[y] + 1;
          }
        }
      }
    }
    return 0;
  }

  vector<int> FindNeighbors(const int x) {
    const string& word = words_[x];
    string pattern = word;
    vector<int> neighbors;
    neighbors.reserve(16);
    for (size_t i = 0, e = pattern.length(); i != e; i++) {
      pattern[i] = '*';
      auto iter = pattern_words_.find(pattern);
      if (iter != pattern_words_.end()) {
        for (int y : iter->second) {
          if (y != x) {
            neighbors.push_back(y);
          }
        }
      }
      pattern[i] = word[i];
    }
    return neighbors;
  }

  vector<string> words_;
  bool bidirectional_;
  unordered_map<string, vector<int>> pattern_words_;
};

class Solution {
 public:
  int ladderLength(const string& begin, const string& end,
                   vector<string> words) {
    if (find(words.begin(), words.end(), begin) == words.end()) {
      words.push_back(begin);
    }

    BFS bfs(words, /*bidirectional=*/true);
    return bfs.Search(begin, end);
  }
};

TEST(WordLadderTest, Exists) {
  EXPECT_EQ(5, Solution().ladderLength(
                   "hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}));
}

TEST(WordLadderTest, NotExists) {
  EXPECT_EQ(0, Solution().ladderLength("hit", "cog",
                                       {"hot", "dot", "dog", "lot", "log"}));
}

TEST(WordLadderTest, ForkJoin) {
  // aaa -> aab -> bab -> bac -> cac
  //     \---> aaz ---> caz ---/
  vector<string> words({"aaa", "aab", "bab", "bac", "cac", "aaz", "caz"});
  sort(words.begin(), words.end());
  // Try all possible permutations to improve test coverage.
  do {
    EXPECT_EQ(4, Solution().ladderLength("aaa", "cac", words));
  } while (next_permutation(words.begin(), words.end()));
}

void BM_LargeDictionary(benchmark::State& state) {
  const string begin = "charge";
  const string end = "comedo";
  const vector<string> words(
      {"shanny", "shinny", "whinny", "whiney", "shiver", "sharer", "scarer",
       "scaler", "render", "fluxes", "teases", "starks", "clinks", "messrs",
       "crewed", "donner", "blurts", "bettye", "powell", "castes", "hackee",
       "hackle", "heckle", "deckle", "decile", "defile", "define", "refine",
       "repine", "rapine", "ravine", "raving", "roving", "chased", "roping",
       "coping", "coming", "homing", "pointy", "hominy", "homily", "homely",
       "comely", "comedy", "comedo", "vagues", "crocus", "spiked", "bobbed",
       "dourer", "smells", "feared", "wooden", "stings", "loafer", "pleads",
       "gaiter", "meeter", "denser", "bather", "deaves", "wetted", "pleats",
       "cadger", "curbed", "grover", "hinged", "budget", "gables", "larked",
       "flunks", "fibbed", "bricks", "bowell", "yonder", "grimes", "clewed",
       "triads", "legion", "lacier", "ridden", "bogied", "camper", "damien",
       "spokes", "flecks", "goosed", "snorer", "choked", "choler", "leakey",
       "vagued", "flumes", "scanty", "bugger", "tablet", "nilled", "julies",
       "roomed", "ridges", "snared", "singes", "slicks", "toiled", "verged",
       "shitty", "clicks", "farmed", "stunts", "dowsed", "brisks", "skunks",
       "linens", "hammer", "naiver", "duster", "elates", "kooked", "whacky",
       "mather", "loomed", "soured", "mosses", "keeled", "drains", "drafty",
       "cricks", "glower", "brayed", "jester", "mender", "burros", "arises",
       "barker", "father", "creaks", "prayed", "bulges", "heaped", "called",
       "volley", "girted", "forded", "huffed", "bergen", "grated", "douses",
       "jagger", "grovel", "lashes", "creeds", "bonier", "snacks", "powder",
       "curled", "milker", "posers", "ribbed", "tracts", "stoked", "russel",
       "bummer", "cusses", "gouged", "nailed", "lobbed", "novels", "stands",
       "caches", "swanks", "jutted", "zinged", "wigged", "lunges", "divers",
       "cranny", "pinter", "guides", "tigers", "traces", "berber", "purges",
       "hoaxer", "either", "bribed", "camped", "funked", "creaky", "noises",
       "paused", "splits", "morrow", "faults", "ladies", "dinged", "smoker",
       "calved", "deters", "kicker", "wisher", "ballad", "filled", "fobbed",
       "tucker", "steams", "rubber", "staled", "chived", "warred", "draped",
       "curfew", "chafed", "washer", "tombed", "basket", "limned", "rapped",
       "swills", "gashed", "loaner", "settee", "layers", "bootee", "rioted",
       "prance", "sharps", "wigner", "ranted", "hanker", "leaden", "groped",
       "dalian", "robbed", "peeled", "larder", "spoofs", "pushed", "hallie",
       "maiden", "waller", "pashas", "grains", "pinked", "lodged", "zipper",
       "sneers", "bootie", "drives", "former", "deepen", "carboy", "snouts",
       "fained", "wilmer", "trance", "bugles", "chimps", "deeper", "bolder",
       "cupped", "mauser", "pagers", "proven", "teaser", "plucky", "curved",
       "shoots", "barged", "mantes", "reefer", "coater", "clotho", "wanner",
       "likens", "swamis", "troyes", "breton", "fences", "pastas", "quirky",
       "boiler", "canoes", "looted", "caries", "stride", "adorns", "dwells",
       "hatred", "cloths", "rotted", "spooks", "canyon", "lances", "denied",
       "beefed", "diaper", "wiener", "rifled", "leader", "ousted", "sprays",
       "ridged", "mousey", "darken", "guiled", "gasses", "suited", "drools",
       "bloody", "murals", "lassie", "babied", "fitter", "lessee", "chiles",
       "wrongs", "malian", "leaves", "redder", "funnel", "broths", "gushes",
       "grants", "doyens", "simmer", "locked", "spoors", "berger", "landed",
       "mosley", "scorns", "whiten", "hurled", "routed", "careen", "chorus",
       "chasms", "hopped", "cadged", "kicked", "slewed", "shrewd", "mauled",
       "saucer", "jested", "shriek", "giblet", "gnarls", "foaled", "roughs",
       "copses", "sacked", "blends", "slurps", "cashew", "grades", "cramps",
       "radius", "tamped", "truths", "cleans", "creams", "manner", "crimps",
       "hauled", "cheery", "shells", "asters", "scalps", "quotas", "clears",
       "clover", "weeder", "homers", "pelted", "hugged", "marked", "moaned",
       "steely", "jagged", "glades", "goshes", "masked", "ringer", "eloped",
       "vortex", "gender", "spotty", "harken", "hasten", "smiths", "mulled",
       "specks", "smiles", "vainer", "patted", "harden", "nicked", "dooley",
       "begged", "belief", "bushel", "rivers", "sealed", "neuter", "legged",
       "garter", "freaks", "server", "crimea", "tossed", "wilted", "cheers",
       "slides", "cowley", "snotty", "willed", "bowled", "tortes", "pranks",
       "yelped", "slaved", "silver", "swords", "miners", "fairer", "trills",
       "salted", "copsed", "crusts", "hogged", "seemed", "revert", "gusted",
       "pixies", "tamika", "franks", "crowed", "rocked", "fisher", "sheers",
       "pushes", "drifts", "scouts", "sables", "sallie", "shiner", "coupes",
       "napped", "drowse", "traced", "scenes", "brakes", "steele", "beater",
       "buries", "turned", "luther", "bowers", "lofted", "blazer", "serves",
       "cagney", "hansel", "talker", "warmed", "flirts", "braced", "yukked",
       "milken", "forged", "dodder", "strafe", "blurbs", "snorts", "jetted",
       "picket", "pistil", "valved", "pewter", "crawls", "strews", "railed",
       "clunks", "smiled", "dealer", "cussed", "hocked", "spited", "cowers",
       "strobe", "donned", "brawls", "minxes", "philby", "gavels", "renter",
       "losses", "packet", "defied", "hazier", "twines", "balled", "gaoled",
       "esther", "narrow", "soused", "crispy", "souped", "corned", "cooley",
       "rioter", "talley", "keaton", "rocker", "spades", "billie", "mattel",
       "billet", "horton", "navels", "sander", "stoker", "winded", "wilder",
       "cloyed", "blazed", "itched", "docked", "greene", "boozed", "ticket",
       "temped", "capons", "bravos", "rinded", "brandi", "massed", "sobbed",
       "shapes", "yippee", "script", "lesion", "mallet", "seabed", "medals",
       "series", "phases", "grower", "vertex", "dented", "tushed", "barron",
       "toffee", "bushes", "mouser", "zenger", "quaked", "marley", "surfed",
       "harmed", "mormon", "flints", "shamed", "forgot", "jailor", "boater",
       "sparer", "shards", "master", "pistol", "tooted", "banned", "drover",
       "spices", "gobbed", "corals", "chucks", "kitten", "whales", "nickel",
       "scrape", "hosted", "hences", "morays", "stomps", "marcel", "hummed",
       "wonder", "stoves", "distil", "coffer", "quaker", "curler", "nurses",
       "cabbed", "jigger", "grails", "manges", "larger", "zipped", "rovers",
       "stints", "nudges", "marlin", "exuded", "storey", "pester", "longer",
       "creeps", "meaner", "wallop", "dewier", "rivera", "drones", "valued",
       "bugled", "swards", "cortes", "charts", "benson", "wreaks", "glares",
       "levels", "smithy", "slater", "suites", "paired", "fetter", "rutted",
       "levied", "menses", "wither", "woolly", "weeded", "planed", "censer",
       "tested", "pulled", "hitter", "slicer", "tartar", "chunky", "whirrs",
       "mewled", "astern", "walden", "hilton", "cached", "geller", "dolled",
       "chores", "sorter", "soothe", "reused", "clumps", "fueled", "hurler",
       "helled", "packed", "ripped", "tanned", "binder", "flames", "teased",
       "punker", "jerked", "cannon", "joists", "whited", "sagged", "heaven",
       "hansen", "grayer", "turfed", "cranks", "stater", "bunted", "horsey",
       "shakes", "brands", "faints", "barber", "gorged", "creamy", "mowers",
       "scrams", "gashes", "knacks", "aeries", "sticks", "altars", "hostel",
       "pumped", "reeves", "litter", "hoaxed", "mushed", "guided", "ripper",
       "bought", "gelled", "ranker", "jennie", "blares", "saloon", "bomber",
       "mollie", "scoops", "coolie", "hollis", "shrunk", "tattle", "sensed",
       "gasket", "dodoes", "mapped", "strips", "dodges", "sailed", "talked",
       "sorted", "lodges", "livest", "pastel", "ladles", "graded", "thrice",
       "thales", "sagger", "mellon", "ganged", "maroon", "fluked", "raised",
       "nannie", "dearer", "lither", "triked", "dorset", "clamps", "lonnie",
       "spates", "larded", "condor", "sinker", "narced", "quaver", "atones",
       "farted", "elopes", "winger", "mottle", "loaned", "smears", "joanne",
       "boozes", "waster", "digger", "swoops", "smokey", "nation", "drivel",
       "ceased", "miffed", "faiths", "pisses", "frames", "fooled", "milled",
       "dither", "crazed", "darryl", "mulder", "posses", "sumter", "weasel",
       "pedals", "brawny", "charge", "welted", "spanks", "sallow", "joined",
       "shaker", "blocks", "mattie", "swirls", "driver", "belles", "chomps",
       "blower", "roared", "ratted", "hailed", "taunts", "steamy", "parrot",
       "deafer", "chewed", "spaces", "cuffed", "molded", "winked", "runnel",
       "hollow", "fluted", "bedded", "crepes", "stakes", "vested", "parley",
       "burton", "loiter", "massey", "carnap", "closed", "bailed", "milder",
       "heists", "morale", "putter", "snyder", "damion", "conned", "little",
       "pooped", "ticced", "cocked", "halves", "wishes", "francs", "goblet",
       "carlin", "pecked", "julius", "raster", "shocks", "dawned", "loosen",
       "swears", "buried", "peters", "treats", "noshed", "hedges", "trumps",
       "rabies", "ronnie", "forces", "ticked", "bodies", "proved", "dadoes",
       "halved", "warner", "divest", "thumbs", "fettle", "ponies", "testis",
       "ranked", "clouts", "slates", "tauted", "stools", "dodged", "chancy",
       "trawls", "things", "sorrow", "levies", "glides", "battle", "sauced",
       "doomed", "seller", "strove", "ballet", "bumper", "gooses", "foiled",
       "plowed", "glints", "chanel", "petals", "darted", "seared", "trunks",
       "hatter", "yokels", "vanned", "tweedy", "rubles", "crones", "nettie",
       "roofed", "dusted", "dicker", "fakers", "rusted", "bedder", "darrin",
       "bigger", "baylor", "crocks", "niches", "tented", "cashed", "splats",
       "quoted", "soloed", "tessie", "stiles", "bearer", "hissed", "soiled",
       "adored", "bowery", "snakes", "wagers", "rafter", "crests", "plaids",
       "cordon", "listed", "lawson", "scared", "brazos", "horded", "greens",
       "marred", "mushes", "hooper", "halter", "ration", "calked", "erodes",
       "plumed", "mummer", "pinged", "curios", "slated", "ranter", "pillow",
       "frills", "whaled", "bathos", "madden", "totted", "reamed", "bellow",
       "golfer", "seaman", "barred", "merger", "hipped", "silken", "hastes",
       "strays", "slinks", "hooted", "convex", "singed", "leased", "bummed",
       "leaner", "molted", "naught", "caters", "tidied", "forges", "sealer",
       "gulled", "plumps", "racket", "fitted", "rafted", "drapes", "nasser",
       "tamara", "winced", "juliet", "ledger", "bettie", "howell", "reeved",
       "spiced", "thebes", "apices", "dorsey", "welled", "feeler", "warded",
       "reader", "folded", "lepers", "cranky", "bosses", "ledges", "player",
       "yellow", "lunged", "mattes", "confer", "malign", "shared", "brandy",
       "filmed", "rhinos", "pulsed", "rouses", "stones", "mixers", "cooped",
       "joiner", "papped", "liston", "capote", "salvos", "wicker", "ciders",
       "hoofed", "wefted", "locket", "picker", "nougat", "limpid", "hooter",
       "jailer", "peaces", "mashes", "custer", "wallis", "purees", "trends",
       "irater", "honied", "wavers", "tanner", "change", "hinges", "tatted",
       "cookie", "catnap", "carton", "crimed", "betted", "veined", "surges",
       "rumped", "merlin", "convey", "placid", "harped", "dianna", "hookey",
       "nobles", "carted", "elided", "whined", "glover", "bleats", "stales",
       "husker", "hearer", "tartan", "weaker", "skewer", "lumbar", "temper",
       "gigged", "gawked", "mayors", "pigged", "gather", "valves", "mitten",
       "largos", "boreas", "judges", "cozens", "censor", "frilly", "dumbed",
       "downer", "jogger", "scolds", "danced", "floras", "funded", "lumped",
       "dashes", "azores", "quites", "chunks", "washed", "duller", "bilges",
       "cruels", "brooks", "fishes", "smoked", "leaped", "hotter", "trials",
       "heaves", "rouges", "kissed", "sleety", "manses", "spites", "starts",
       "banded", "clings", "titted", "vetoed", "mister", "mildew", "wailed",
       "sheets", "peeked", "passer", "felted", "broken", "lieges", "ruffed",
       "bracts", "buster", "muffed", "lanker", "breaks", "coffey", "sighed",
       "charms", "balded", "kisser", "booths", "leaven", "cheeps", "billed",
       "lauder", "bumped", "career", "stocks", "airier", "limped", "jeanie",
       "roamed", "carves", "lilted", "router", "bonnie", "denver", "briggs",
       "steeps", "nerves", "oinked", "bucked", "hooves", "dancer", "burris",
       "parked", "swells", "collie", "perked", "cooler", "fopped", "wedder",
       "malted", "sabers", "lidded", "conner", "rogues", "fought", "dapper",
       "purled", "crowds", "barnes", "bonner", "globed", "goners", "yankee",
       "probes", "trains", "sayers", "jersey", "valley", "vatted", "tauter",
       "dulled", "mucked", "jotted", "border", "genres", "banked", "filter",
       "hitler", "dipper", "dollie", "sieves", "joliet", "tilted", "checks",
       "sports", "soughs", "ported", "causes", "gelded", "mooter", "grills",
       "parred", "tipped", "placer", "slayer", "glided", "basked", "rinses",
       "tamper", "bunged", "nabbed", "climbs", "faeces", "hanson", "brainy",
       "wicket", "crowns", "calmed", "tarred", "spires", "deanne", "gravel",
       "messes", "snides", "tugged", "denier", "moslem", "erased", "mutter",
       "blahed", "hunker", "fasten", "garbed", "cracks", "braked", "rasped",
       "ravens", "mutton", "tester", "tories", "pinker", "titled", "arisen",
       "softer", "woolen", "disses", "likest", "dicier", "nagged", "lipton",
       "plumbs", "manged", "faulty", "sacred", "whiter", "erases", "padres",
       "haired", "captor", "metals", "cardin", "yowled", "trusts", "revels",
       "boxers", "toured", "spouts", "sodded", "judged", "holley", "figged",
       "pricey", "lapses", "harper", "beaned", "sewers", "caused", "willie",
       "farmer", "pissed", "bevies", "bolled", "bugler", "votive", "person",
       "linton", "senses", "supped", "mashed", "pincer", "wetter", "tangos",
       "sticky", "lodger", "loader", "daunts", "peaked", "moused", "sleeps",
       "lasted", "tasked", "awards", "lovely", "gushed", "spurts", "canter",
       "mantis", "coaled", "groans", "dannie", "oopses", "sneaky", "vogues",
       "mobile", "plumes", "chides", "theses", "marcia", "parser", "flexed",
       "stayed", "fouler", "tusked", "quartz", "daubed", "clancy", "rouged",
       "flaked", "norton", "dunner", "corded", "shelly", "hester", "fucker",
       "polled", "rodger", "yeager", "zinced", "livens", "browne", "gonged",
       "pubbed", "sapped", "thrive", "placed", "jensen", "moises", "scopes",
       "stumpy", "stocky", "heller", "levers", "morals", "wheres", "gasped",
       "jobber", "leaved", "champs", "rosier", "pallet", "shooed", "parses",
       "bender", "closet", "pureed", "routes", "verges", "bulled", "foster",
       "rummer", "molten", "condos", "better", "cotter", "lassos", "grafts",
       "vendor", "thrace", "codded", "tinker", "bullet", "beaker", "garden",
       "spiels", "popper", "skills", "plated", "farrow", "flexes", "esters",
       "brains", "handel", "puller", "dickey", "creeks", "ballot", "singer",
       "sicker", "spayed", "spoils", "rubier", "missed", "framed", "bonnet",
       "molder", "mugger", "waived", "taster", "robles", "tracks", "nearer",
       "lister", "horsed", "drakes", "lopped", "lubber", "busied", "button",
       "eluded", "ceases", "sought", "realer", "lasers", "pollen", "crisps",
       "binned", "darrel", "crafty", "gleams", "lonely", "gordon", "harley",
       "damian", "whiles", "wilton", "lesser", "mallow", "kenyon", "wimped",
       "scened", "risked", "hunter", "rooter", "ramses", "inches", "goaded",
       "ferber", "freaky", "nerved", "spoken", "lovers", "letter", "marrow",
       "bulbed", "braver", "sloped", "breads", "cannes", "bassos", "orated",
       "clever", "darren", "bredes", "gouger", "servos", "trites", "troths",
       "flunky", "jammed", "bugged", "watter", "motive", "humped", "writer",
       "pestle", "rilled", "packer", "foists", "croats", "floury", "napier",
       "floors", "scotty", "sevens", "harrow", "welter", "quacks", "daybed",
       "lorded", "pulses", "pokier", "fatten", "midges", "joints", "snoopy",
       "looter", "monies", "canted", "riffed", "misses", "bunker", "piston",
       "yessed", "earner", "hawked", "wedged", "brewer", "nested", "graver",
       "hoaxes", "slaves", "pricks", "magpie", "bernie", "rapier", "roster",
       "poohed", "corner", "trysts", "rogers", "whirls", "bathed", "teasel",
       "opener", "minced", "sister", "dreamy", "worker", "rinked", "panted",
       "triton", "mervin", "snowed", "leafed", "thinks", "lesson", "millet",
       "larson", "lagged", "likely", "stormy", "fortes", "hordes", "wovens",
       "kinked", "mettle", "seated", "shirts", "solver", "giants", "jilted",
       "leaded", "mendez", "lowers", "bidder", "greats", "pepped", "flours",
       "versus", "canton", "weller", "cowper", "tapped", "dueled", "mussed",
       "rubies", "bonged", "steals", "formed", "smalls", "sculls", "docket",
       "ouster", "gunned", "thumps", "curred", "withes", "putted", "buttes",
       "bloats", "parsed", "galley", "preses", "tagged", "hanger", "planes",
       "chords", "shafts", "carson", "posits", "zinger", "solves", "tensed",
       "tastes", "rinsed", "kenned", "bitten", "leslie", "chanty", "candor",
       "daises", "baggie", "wedded", "paints", "moored", "haloed", "hornet",
       "lifted", "fender", "guiles", "swifts", "flicks", "lancer", "spares",
       "pellet", "passed", "finked", "joanna", "bidden", "swamps", "lapped",
       "leered", "served", "shirrs", "choker", "limper", "marker", "nudged",
       "triter", "thanks", "peered", "bruins", "loaves", "fabled", "lathes",
       "pipers", "hooped", "orates", "burned", "swines", "sprats", "warder",
       "colder", "crazes", "reined", "prized", "majors", "darrow", "waifed",
       "rooked", "rickey", "patter", "shrive", "gropes", "gassed", "throve",
       "region", "weaken", "hettie", "walton", "galled", "convoy", "wesson",
       "exudes", "tinted", "clanks", "blinks", "slacks", "stilts", "franny",
       "socket", "wished", "kidded", "knotty", "turves", "cashes", "geared",
       "sunned", "glowed", "sadden", "harlem", "testes", "sweets", "becket",
       "blazes", "batter", "fellow", "clovis", "copier", "shaped", "husked",
       "gimlet", "rooney", "taints", "sashes", "bossed", "cootie", "franck",
       "probed", "bagged", "smocks", "batten", "spared", "chills", "relics",
       "meyers", "grader", "tromps", "dimmer", "pasted", "pepper", "capped",
       "played", "junket", "easier", "palmed", "pander", "vaguer", "bulged",
       "dissed", "borges", "raises", "wallow", "jigged", "bogged", "burped",
       "neater", "rammed", "fibers", "castor", "skirts", "cancer", "tilled",
       "spored", "dander", "denims", "budges", "trucks", "sowers", "yapped",
       "cadges", "wrists", "hacker", "graved", "vipers", "noshes", "minted",
       "lessor", "cassia", "wrecks", "hidden", "brando", "honeys", "chilli",
       "ragged", "breded", "punier", "stacey", "sisses", "jocked", "croaks",
       "dinned", "walker", "heston", "flares", "coined", "cannot", "chocks",
       "leases", "wander", "balder", "warmer", "bawled", "donnie", "damson",
       "header", "chilly", "models", "simper", "watery", "milked", "poises",
       "combed", "toilet", "gallop", "sonnet", "loosed", "yawned", "splays",
       "pauses", "bother", "graphs", "shrews", "scones", "manuel", "milers",
       "hotels", "bennie", "flores", "spells", "grimed", "tenses", "staged",
       "puffer", "posies", "motion", "fudged", "fainer", "tatter", "seraph",
       "nansen", "months", "muppet", "tamera", "shaman", "falser", "becker",
       "lisbon", "clefts", "weeper", "mendel", "girder", "takers", "torsos",
       "forked", "dances", "stated", "yelled", "scants", "frothy", "rolled",
       "yodels", "listen", "craned", "brooms", "suffer", "easter", "shills",
       "craves", "bleeps", "belled", "dished", "bordon", "zither", "jacket",
       "lammer", "kirked", "shaved", "atoned", "frumpy", "nosier", "vender",
       "graced", "clingy", "chants", "wrests", "cursed", "prunes", "tarter",
       "stripe", "coffee", "veiled", "tweeds", "shrine", "spines", "kegged",
       "melvin", "gasser", "market", "marten", "peeped", "sanger", "somber",
       "spider", "netted", "radium", "slings", "scarfs", "mended", "creels",
       "shaves", "payers", "bunked", "movers", "beings", "conked", "cozies",
       "benton", "codger", "prints", "gusset", "longed", "burner", "jambed",
       "mullet", "fogged", "scores", "carbon", "sleeks", "helped", "waxier",
       "gilded", "harlot", "winces", "tenser", "lowell", "ramsey", "kennan",
       "booted", "beaver", "rested", "shouts", "hickey", "looped", "swings",
       "wonted", "dilled", "defers", "lolled", "pupped", "cruets", "solved",
       "romper", "defter", "chokes", "kithed", "garnet", "bookie", "stared",
       "stares", "latter", "lazies", "fanned", "wagged", "dunces", "corked",
       "cloned", "prided", "baxter", "pusses", "boomed", "masses", "warren",
       "weaves", "delves", "handed", "merton", "lusher", "hepper", "gibber",
       "sender", "parsec", "snares", "masher", "seamed", "sweats", "welles",
       "gagged", "curter", "mother", "beeped", "vealed", "shoved", "slaver",
       "hacked", "gutted", "ranged", "bashed", "closer", "storks", "meshed",
       "cortex", "copper", "severn", "gripes", "carlos", "scares", "crates",
       "boiled", "ginned", "mouses", "raided", "greyed", "verier", "slopes",
       "fenced", "sniper", "priced", "flawed", "buffed", "spacey", "favors",
       "platen", "miller", "walled", "cutter", "skated", "holier", "beamed",
       "waiter", "drowns", "clomps", "quarks", "bested", "frisks", "purged",
       "scalds", "marian", "flower", "howled", "plover", "bikers", "trails",
       "hagged", "smirks", "sitter", "carmen", "lanced", "plants", "nobler",
       "yakked", "thesis", "lassen", "margin", "wagner", "sifter", "houses",
       "screws", "booker", "dormer", "meters", "padded", "loaded", "cartel",
       "sutton", "willis", "chatty", "dunked", "dreamt", "dalton", "fables",
       "coveys", "muller", "shanty", "adders", "tailor", "helper", "liters",
       "butted", "maiman", "hollie", "gallon", "xavier", "shrank", "mickey",
       "rather", "powers", "keened", "doused", "kisses", "flanks", "dotted",
       "phased", "dumped", "linger", "kramer", "spaced", "soften", "strife",
       "rowers", "hovers", "crimes", "crooks", "carrel", "braces", "lander",
       "shrove", "skulks", "banker", "itches", "dropsy", "misted", "pulped",
       "cloche", "fawned", "states", "teared", "beeper", "raider", "groves",
       "livery", "aerier", "keenan", "severe", "sabres", "bogies", "coated",
       "harlow", "tanked", "mellow", "cozier", "shanks", "spooky", "blamed",
       "tricks", "sleets", "punted", "jumped", "caxton", "warped", "halley",
       "frisky", "shines", "skater", "lumber", "truces", "sliced", "gibbet",
       "narked", "chives", "graves", "gummed", "holler", "glazes", "nieves",
       "hushed", "nought", "prated", "chored", "cloudy", "kidder", "huston",
       "straws", "twined", "gifted", "rodney", "haloes", "france", "wirier",
       "mercia", "rubbed", "coaxed", "sumner", "snipes", "nipper", "leiden",
       "madman", "margie", "footed", "firmed", "budded", "froths", "senior",
       "hoover", "tailed", "glider", "straps", "stalks", "billow", "racked",
       "javier", "zoomed", "shades", "whores", "braids", "roused", "sudden",
       "dogies", "fencer", "snaked", "flings", "traded", "gunner", "snider",
       "staten", "levees", "lathed", "sailor", "waited", "muster", "clothe",
       "lulled", "cargos", "revved", "sooths", "flamed", "borers", "feller",
       "bladed", "oliver", "collin", "wusses", "murder", "parted", "jailed",
       "frayed", "doored", "cheeks", "misled", "belted", "winter", "merges",
       "shaven", "fudges", "tabbed", "forget", "sloths", "cachet", "mealed",
       "sassed", "salter", "haunts", "ranger", "rivets", "deeded", "reaped",
       "damped", "crated", "youths", "whacks", "tamers", "misery", "seeped",
       "eerier", "tiller", "busses", "gloved", "hushes", "cronus", "pruned",
       "casket", "direst", "guilds", "motley", "spools", "fevers", "snores",
       "greece", "elides", "waists", "rattle", "trader", "juster", "rashes",
       "stoney", "pipped", "solder", "sinner", "prides", "rugged", "steers",
       "gnarly", "titter", "cities", "walter", "stolen", "steaks", "hawker",
       "weaned", "jobbed", "jacked", "pikers", "hipper", "spoilt", "beeves",
       "craved", "gotten", "balked", "sherry", "looney", "crisis", "callie",
       "swiped", "fished", "rooted", "bopped", "bowler", "escher", "chumps",
       "jerrod", "lefter", "snooty", "fillet", "scales", "comets", "lisped",
       "decked", "clowns", "horned", "robber", "bottle", "reeled", "crapes",
       "banter", "martel", "dowels", "brandt", "sweeps", "heeled", "tabled",
       "manors", "danger", "dionne", "prayer", "decker", "millie", "boated",
       "damned", "horses", "globes", "failed", "lammed", "nigher", "joyner",
       "sobers", "chided", "tipper", "parcel", "flakes", "fugger", "elated",
       "hinder", "hopper", "crafts", "wipers", "badder", "jessie", "matted",
       "wafted", "pealed", "cheats", "elites", "torres", "bushed", "sneaks",
       "tidies", "brings", "stalls", "payees", "zonked", "danker", "poshes",
       "smelts", "stoops", "warden", "chicks", "ramsay", "budged", "firmer",
       "glazed", "heated", "slices", "hovels", "belied", "shifts", "pauper",
       "tinges", "weston", "casted", "titles", "droves", "roomer", "modals",
       "seamen", "wearer", "blonde", "berlin", "libbed", "tensor", "hokier",
       "lambed", "graped", "headed", "copped", "eroses", "fagged", "filler",
       "keener", "stages", "civets", "spills", "tithed", "sullen", "sucked",
       "briton", "whaler", "hooded", "tittle", "bucket", "furled", "darned",
       "planet", "clucks", "batted", "dagger", "brides", "severs", "pathos",
       "grainy", "relied", "carpel", "makers", "lancet", "slowed", "messed",
       "ravels", "faster", "gabbed", "chance", "grayed", "santos", "spends",
       "chinos", "saints", "swirly", "dories", "wilson", "milton", "clangs",
       "manual", "nodded", "signer", "stript", "etched", "vaster", "wastes",
       "stored", "minces", "purred", "marvin", "pinned", "skulls", "heaved",
       "wadded", "fowled", "hashed", "mullen", "relief", "hatted", "primed",
       "chaffs", "canned", "lackey", "showed", "shandy", "chases", "maggie",
       "deafen", "bussed", "differ", "worked", "marted", "ducked", "socked",
       "fussed", "greyer", "herder", "trusty", "follow", "samson", "babies",
       "whorls", "stanks", "manson", "cranes", "murrow", "shrink", "genius",
       "holder", "lenses", "yucked", "termed", "ruined", "junker", "belies",
       "joshed", "cooled", "basted", "greeks", "fuller", "healer", "carver",
       "havens", "drunks", "sucker", "lotion", "glared", "healed", "pocked",
       "rifles", "weaved", "canoed", "punter", "hinton", "settle", "boobed",
       "hinted", "scored", "harder", "status", "sloven", "hayden", "golfed",
       "scoots", "bloods", "slaked", "jugged", "louses", "cassie", "shaded",
       "rushed", "pitied", "barked", "honked", "rasher", "forced", "shaver",
       "vowels", "holden", "pelvis", "blades", "chests", "preyer", "floods",
       "deanna", "cation", "mapper", "falter", "dabbed", "mocker", "nestle",
       "shucks", "heeded", "ticker", "binges", "summer", "slumps", "lusted",
       "scampi", "crofts", "gorges", "pardon", "torses", "smokes", "lashed",
       "bailey", "jabbed", "calmer", "preset", "forbes", "hasted", "wormed",
       "winged", "minors", "banner", "grazed", "hewers", "kernel", "jolted",
       "sniped", "clunky", "ratios", "blinds", "ganges", "misers", "spikes",
       "riders", "hallow", "grumpy", "barren", "summed", "infers", "places",
       "jarred", "killer", "plaint", "goofed", "subbed", "prudes", "sipped",
       "kookie", "whines", "droopy", "palled", "cherry", "proves", "mobbed",
       "spaded", "cheese", "pluses", "bathes", "motels", "spewed", "soaked",
       "howler", "puffed", "malled", "shrike", "slided", "fulled", "pouted",
       "shames", "lessen", "ringed", "teemed", "grands", "linked", "wooten",
       "feuded", "deaden", "scents", "flutes", "salton"});
  Solution s;
  for (auto _ : state) {
    s.ladderLength(begin, end, words);
  }
}

BENCHMARK(BM_LargeDictionary)->Unit(benchmark::kMillisecond);
