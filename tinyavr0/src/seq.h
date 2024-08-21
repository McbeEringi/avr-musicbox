#ifndef SEQ_H
#define SEQ_H

const uint8_t dw3level[]={// 33bytes
	60,0,
	0,32,64,149,149,149,149,156,147,156,151,156,70,149,
	0,32,64,144,139,138,137,140,135,140,138,140,70,137,1,
	0,0
};
const uint8_t famima[]={// 34bytes
	20,0,
	0,32,64,150,146,137,146,148,98,217,148,150,148,137,67,146,
	0,32,65,140,134,98,209,96,196,137,137,67,134,1,
	0,0
};
const uint8_t kakko[]={// 35bytes
	40,1,
	0,32,65,161,99,217,161,217,161,164,96,228,225,217,225,99,219,162,216,155,212,155,162,64,162,155,152,155,67,153,1,
	0,0
};
const uint8_t ofuro[]={// 98bytes
	30,0,
	0,32,64,151,149,97,212,151,160,219,151,162,224,99,228,160,155,97,217,165,162,224,219,101,224,
	0,32,64,140,140,128,132,132,132,130,133,97,197,132,135,135,135,132,135,135,135,133,137,137,137,135,144,135,146,144,148,148,146,208,
	0,32,64,140,140,140,135,135,135,140,139,97,203,156,144,144,144,156,144,144,144,156,146,146,146,156,148,156,149,148,151,151,149,212,1,
	0,0
};
const uint8_t petrouchka[]={// 218bytes
	65,1,
	0,32,69,149,65,151,69,152,65,149,65,152,152,151,149,67,151,144,69,151,65,152,69,154,65,151,65,154,154,152,151,149,144,64,149,151,152,154,67,160,65,165,145,67,163,65,165,163,161,161,160,154,67,160,149,65,156,67,161,154,160,65,152,151,144,152,151,149,144,64,149,151,152,154,67,160,65,165,145,67,163,65,165,163,161,161,160,154,67,160,149,65,156,67,161,154,160,65,152,154,160,162,164,67,165,149,
	0,40,67,165,176,181,184,181,176,180,183,180,170,177,183,176,65,180,183,67,184,65,181,176,165,176,184,181,64,183,181,180,181,65,177,176,170,181,176,177,165,176,64,184,181,183,184,67,170,65,177,181,67,165,65,184,181,67,176,65,180,183,67,184,65,181,176,165,176,184,181,64,183,181,180,181,65,177,176,170,181,176,177,165,176,64,184,181,183,184,67,170,65,177,181,67,165,65,184,181,67,183,65,180,176,71,165,1,
	0,0
};

// const uint8_t surfboard_[]={// 259bytes
// 	50,1,
// 	0,42,64,185,185,188,183,183,188,182,182,188,180,180,188,179,179,188,178,178,188,179,179,188,180,180,188,181,181,188,183,183,188,183,183,188,181,181,188,180,180,188,178,178,188,177,177,188,176,176,188,177,177,188,178,178,188,179,179,188,181,181,188,181,181,188,179,179,188,178,178,188,176,176,188,170,170,172,169,169,172,181,181,188,179,179,188,178,178,188,176,176,188,170,170,172,169,169,172,65,179,178,64,179,181,67,182,64,181,179,65,179,178,64,179,181,67,182,65,188,
// 	0,40,67,151,146,151,146,151,146,144,151,149,160,149,160,149,160,154,149,147,154,147,154,146,153,146,153,69,151,152,151,152,
// 	0,38,64,177,177,187,177,177,187,177,177,187,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,187,187,177,187,177,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,177,177,187,177,177,187,177,177,187,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,187,187,177,187,177,75,188,188,1,
// 	0,0
// };
const uint8_t yobikomi[]={// 324bytes
	65,129,
	0,35,64,153,156,99,217,155,156,153,156,150,156,97,217,220,153,156,99,217,155,156,153,156,150,156,97,217,220,146,156,146,156,146,156,148,156,100,214,156,146,156,214,156,153,156,103,217,146,156,146,156,146,156,148,156,214,146,156,146,156,146,156,148,156,214,148,156,148,156,148,156,146,156,97,212,220,214,220,217,220,215,220,214,220,212,220,
	0,42,65,172,64,169,98,236,169,236,169,169,97,236,169,98,236,169,236,169,236,169,169,97,236,169,98,236,171,236,171,236,171,171,97,236,171,98,236,171,236,171,236,171,171,97,236,171,98,236,171,236,171,236,171,171,97,236,171,98,236,171,236,171,236,171,171,97,236,171,98,236,169,236,169,236,169,169,97,236,169,98,236,169,236,169,236,169,169,65,172,169,
	0,42,65,172,64,166,98,236,166,236,166,166,97,236,166,98,236,166,236,166,236,166,166,97,236,166,98,236,166,236,166,236,166,166,97,236,166,98,236,166,236,166,236,166,166,97,236,166,98,236,167,236,167,236,167,167,97,236,167,98,236,167,236,167,236,167,167,97,236,167,98,236,164,236,164,236,164,164,97,236,164,98,236,164,236,164,236,164,164,65,172,164,
	0,43,67,162,153,162,153,162,153,98,226,96,217,97,226,225,155,150,155,150,155,150,98,219,96,214,97,219,217,151,146,151,162,151,146,215,210,215,219,153,148,153,148,153,148,225,219,153,1,
	0,0
};
const uint8_t jingle[]={// 174bytes
	65,128,
	0,34,65,137,150,148,146,101,201,137,137,150,148,146,103,203,139,151,150,148,101,209,153,155,153,151,148,214,137,137,150,148,146,101,201,137,137,150,148,146,103,203,139,151,150,148,153,153,153,153,155,153,151,148,99,210,217,
	0,40,67,162,153,162,153,162,163,164,155,164,155,161,153,161,153,162,153,162,153,162,153,162,166,167,166,164,164,153,153,155,161,162,65,163,
	0,42,65,140,67,166,166,166,166,166,166,167,167,167,167,167,167,167,167,165,166,166,166,166,166,166,166,167,167,167,167,168,168,169,169,169,65,169,
	0,42,65,140,67,169,169,169,169,169,170,171,171,171,171,177,177,176,171,168,169,169,169,169,169,169,170,171,171,171,171,171,171,176,177,178,65,179,1,
	0,0
};
const uint8_t jingle_bell[]={// 335bytes
	70,1,
	0,34,65,137,150,148,146,101,201,137,137,150,148,146,103,203,139,151,150,148,101,209,153,155,153,151,148,214,137,137,150,148,146,101,201,137,137,150,148,146,103,203,139,151,150,148,153,153,153,153,155,153,151,148,99,210,217,150,150,214,150,150,214,150,153,66,146,64,148,65,103,214,151,151,66,151,64,151,65,151,150,150,150,150,148,148,146,99,212,217,150,150,214,150,150,214,150,153,66,146,64,148,65,103,214,151,151,66,151,64,151,65,151,150,150,150,153,153,151,148,101,210,137,
	0,40,67,162,153,162,153,162,163,164,155,164,155,161,153,161,153,162,153,162,153,162,153,162,166,167,166,164,164,153,153,155,161,162,163,162,161,155,153,162,153,162,153,155,151,155,162,164,155,161,153,162,161,155,153,162,153,162,153,155,151,155,162,153,161,162,153,
	0,42,65,140,67,166,166,166,166,166,166,167,167,167,167,167,167,167,167,165,166,166,166,166,166,166,166,167,167,167,167,168,168,169,169,169,169,166,166,166,166,166,166,166,166,167,167,166,166,168,168,164,164,166,166,166,166,166,166,166,166,167,167,166,166,167,164,166,65,164,
	0,42,65,140,67,169,169,169,169,169,170,171,171,171,171,177,177,176,171,168,169,169,169,169,169,169,170,171,171,171,171,171,171,176,177,178,179,169,169,169,169,169,169,169,169,171,171,170,169,171,171,169,169,169,169,169,169,169,169,169,169,171,171,169,169,171,171,169,65,169,1,
	0,0
};
const uint8_t nyan[]={// 369bytes
	70,1,
	0,32,97,214,216,64,146,211,139,146,145,203,203,209,210,146,145,139,145,147,150,152,147,150,145,147,139,145,139,211,214,152,147,150,145,147,139,146,147,146,145,139,145,210,139,145,147,150,145,146,145,139,209,203,209,214,216,146,211,139,146,145,203,203,209,210,146,145,139,145,147,150,152,147,150,145,147,139,145,139,211,214,152,147,150,145,147,139,146,147,146,145,139,145,210,139,145,147,150,145,146,145,139,209,203,203,203,134,136,203,134,136,139,145,147,139,148,147,148,150,203,203,134,136,139,134,148,147,145,139,134,131,132,134,203,134,136,203,134,136,139,139,145,147,139,134,136,134,203,139,138,139,134,136,139,148,147,148,150,203,202,203,134,136,203,134,136,139,145,147,139,148,147,148,150,203,203,134,136,139,134,148,147,145,139,134,131,132,134,203,134,136,203,134,136,139,139,145,147,139,134,136,134,203,139,138,139,134,136,139,148,147,148,150,203,209,
	0,40,97,228,228,230,230,227,227,232,232,225,225,230,230,219,219,64,155,162,161,155,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,161,162,163,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,162,161,155,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,161,162,163,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,162,161,155,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,161,162,163,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,162,161,155,228,228,230,230,227,227,232,232,225,225,230,230,219,219,155,161,162,163,1,
	0,0
};
const uint8_t small_world[]={// 419bytes
	65,1,
	0,34,65,139,144,99,210,219,215,153,151,215,214,214,137,139,208,217,214,151,150,212,210,210,139,144,210,151,153,219,153,151,212,153,155,224,155,153,210,224,219,217,103,215,220,101,215,151,99,219,215,101,217,153,103,217,101,217,153,99,224,217,101,219,155,103,219,101,219,155,99,226,219,101,224,160,99,224,155,153,71,146,150,151,220,
	0,46,67,140,65,172,171,172,171,172,171,172,171,188,176,188,176,188,176,188,176,188,176,188,176,188,176,188,176,172,171,172,171,172,171,172,171,172,171,172,171,188,178,188,178,188,180,188,180,188,180,188,180,188,178,188,178,188,176,188,176,172,171,172,171,171,172,172,176,172,171,172,171,172,171,172,171,188,176,188,176,188,176,188,176,188,176,188,176,188,176,188,176,172,171,172,171,172,171,172,171,172,171,172,171,188,178,188,178,188,180,188,180,188,180,188,180,188,178,188,178,188,176,188,176,172,171,172,171,171,172,
	0,44,67,140,65,172,167,172,167,172,167,172,167,172,169,172,169,172,169,172,169,172,169,172,169,172,169,172,169,172,167,172,167,172,167,172,167,172,167,172,167,172,171,172,171,188,176,188,176,188,177,188,177,188,176,188,176,172,169,172,169,172,167,172,167,167,172,172,169,172,167,172,167,172,167,172,167,172,169,172,169,172,169,172,169,172,169,172,169,172,169,172,169,172,167,172,167,172,167,172,167,172,167,172,167,172,171,172,171,188,176,188,176,188,177,188,177,188,176,188,176,172,169,172,169,172,167,172,167,167,172,
	0,40,67,140,151,146,151,146,153,146,153,146,153,146,153,146,151,146,151,146,151,151,155,155,160,160,161,161,162,146,150,153,151,146,151,146,151,146,151,146,153,146,153,146,153,146,153,146,151,146,151,146,151,151,155,155,160,160,161,161,162,146,150,153,151,146,151,1,
	0,0
};
const uint8_t kewpie[]={// 535bytes
	84,0,
	0,34,65,140,96,215,215,151,151,148,148,67,149,65,156,215,215,151,151,145,145,67,146,65,156,215,215,71,151,146,135,67,156,65,151,215,215,148,156,151,156,151,156,156,215,215,149,156,151,156,151,156,156,215,215,148,156,151,156,155,156,153,156,151,150,149,148,146,156,156,215,215,148,156,151,156,151,156,156,215,215,146,156,155,156,155,156,156,217,217,153,156,153,156,162,172,162,156,99,215,96,215,216,217,218,155,151,153,151,148,156,151,156,148,151,156,151,149,156,151,156,149,151,156,151,148,156,151,156,155,156,153,156,151,150,149,148,146,156,156,215,215,148,156,151,156,151,156,156,215,215,149,156,153,156,153,156,160,172,164,172,99,236,162,172,236,160,64,151,152,153,154,65,155,160,140,192,
	0,34,71,140,65,145,145,99,210,220,220,138,138,203,204,140,103,214,208,156,215,99,220,42,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,171,172,171,172,171,172,171,172,169,172,169,172,169,172,169,231,236,236,236,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,167,172,169,172,169,172,169,172,169,172,167,172,167,172,167,172,167,167,172,236,176,188,224,
	0,34,83,140,140,71,149,139,99,204,135,42,65,172,164,172,164,172,164,172,164,172,165,172,165,172,165,172,165,172,164,172,164,172,164,172,164,172,165,172,165,172,165,172,165,172,164,172,164,172,164,172,164,172,167,172,167,172,167,172,167,172,166,172,166,172,166,172,166,111,236,172,164,172,164,172,164,172,164,172,165,172,165,172,165,172,165,172,164,172,164,172,164,172,164,172,165,172,165,172,165,172,165,172,164,172,164,172,164,172,164,172,165,172,165,172,165,172,165,172,164,172,162,172,165,172,165,164,172,99,236,236,208,1,
	0,34,84,140,140,103,212,201,65,140,204,42,67,160,151,144,151,146,151,146,151,160,151,144,151,146,151,146,151,160,151,144,151,146,151,146,151,153,146,150,146,151,156,220,160,151,160,160,151,146,151,151,160,151,160,160,151,146,151,151,160,151,160,160,149,144,149,149,160,151,146,151,65,160,
	0,0
};
// const uint8_t dbfl[]={// 760bytes
// 	70,1,
// 	0,38,67,151,66,151,97,215,151,215,215,67,148,66,148,212,146,210,210,67,148,66,148,208,144,208,208,67,148,66,148,212,146,210,210,67,151,66,151,97,215,151,215,215,67,148,66,148,212,146,210,210,67,148,66,148,208,144,208,208,67,148,66,148,212,146,210,210,34,97,220,208,208,64,146,210,66,144,208,210,67,148,210,64,144,210,66,144,208,210,220,208,208,64,151,215,66,144,208,217,67,151,212,64,149,212,66,146,208,210,220,208,208,64,146,210,66,144,208,210,67,148,210,64,144,210,66,144,208,210,220,208,208,64,151,215,66,144,208,217,67,151,212,64,149,212,66,146,208,210,67,151,212,64,148,210,66,144,208,217,151,64,148,212,149,212,66,146,208,210,151,64,148,212,148,210,66,144,199,208,144,64,135,208,146,212,66,146,208,210,220,210,210,64,144,210,208,210,144,208,66,151,64,148,215,153,215,210,210,144,208,217,215,215,148,210,208,208,151,151,151,217,224,224,162,228,226,226,160,224,233,231,231,169,227,226,224,153,153,153,224,217,224,162,228,226,226,224,162,67,160,231,228,226,224,236,217,224,217,224,64,162,228,226,226,160,224,233,231,231,169,227,226,224,153,153,153,224,217,224,162,228,226,226,224,162,67,160,231,228,226,224,236,217,224,217,224,64,162,228,226,226,224,162,69,160,79,167,64,163,70,162,227,69,162,73,160,
// 	0,40,67,169,66,169,97,233,169,233,233,67,165,66,165,231,167,231,231,67,169,66,169,235,171,235,240,67,165,66,165,231,167,231,231,67,169,66,169,233,169,233,233,67,165,66,165,231,167,231,231,67,169,66,169,235,171,235,240,67,165,66,165,231,167,231,231,67,169,66,169,229,165,229,229,67,176,66,176,231,167,231,231,67,169,66,169,229,165,229,229,67,176,66,176,231,167,231,231,67,169,66,169,229,165,229,229,67,176,66,176,231,167,231,231,67,169,66,169,229,165,229,229,67,176,66,176,231,167,231,231,67,169,66,169,229,165,229,229,67,176,66,176,231,167,231,231,67,169,66,169,229,165,229,229,67,176,66,176,231,167,231,231,67,169,66,169,233,169,233,233,67,165,66,165,231,167,231,231,67,169,66,169,240,176,240,240,67,165,66,165,231,167,231,231,67,165,66,165,240,176,240,240,67,167,66,167,231,169,233,233,67,165,66,165,240,176,240,240,67,167,66,167,231,169,233,233,67,165,66,165,240,176,240,240,67,167,66,167,231,169,233,233,67,165,66,165,240,176,240,240,67,167,66,167,231,169,233,233,67,169,66,169,233,169,233,233,67,165,66,165,231,167,231,231,67,169,66,169,240,176,240,240,67,165,66,165,229,167,231,231,
// 	0,46,67,153,153,153,153,149,149,151,151,153,153,160,160,149,149,151,151,153,153,153,153,149,149,151,151,153,153,160,160,149,149,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,153,153,149,149,151,151,153,153,160,160,149,149,151,151,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,149,149,160,160,151,151,153,153,153,153,153,153,149,149,151,151,153,153,160,160,149,149,151,151,1,
// 	0,0
// };
const uint8_t sanpo[]={// 779bytes
	180,0,
	0,34,71,151,99,215,224,215,224,226,215,226,164,228,165,228,162,224,155,217,107,215,151,99,215,224,215,224,226,215,226,164,228,165,228,162,219,224,217,219,224,236,236,69,146,148,149,150,151,153,155,160,75,162,215,215,215,87,151,75,153,215,213,212,146,153,151,213,212,210,144,151,149,213,212,210,69,144,139,137,139,75,144,208,212,215,160,172,148,151,119,224,151,153,215,103,220,67,144,212,151,75,160,219,67,153,87,151,156,217,67,153,217,75,153,67,160,219,153,119,215,220,103,217,151,217,151,75,146,148,87,144,156,216,67,152,216,123,216,75,151,71,151,123,215,107,213,213,213,71,146,91,148,87,156,208,224,219,103,215,91,153,220,67,153,219,160,75,162,160,155,153,87,151,156,224,67,155,224,151,212,107,224,91,155,220,103,215,67,151,75,153,156,155,156,87,160,172,224,67,155,224,151,75,148,224,123,219,156,103,215,99,215,153,156,155,156,101,224,224,218,216,214,212,211,209,208,208,202,200,198,196,195,193,128,99,208,212,215,160,172,
	0,40,75,160,172,160,172,160,160,160,172,160,172,160,172,160,160,160,172,101,226,228,229,230,231,233,235,240,178,167,167,172,165,165,167,165,164,164,153,153,162,162,167,167,160,160,160,172,160,160,160,160,162,162,151,151,160,155,153,153,162,162,151,151,165,165,165,165,164,164,153,153,162,162,151,151,160,160,160,172,165,165,165,165,164,164,164,164,162,162,167,167,160,160,160,155,153,153,164,164,165,165,165,164,162,162,166,166,167,165,164,162,160,160,160,160,164,164,164,172,165,172,167,172,160,151,160,99,215,217,219,160,160,160,103,224,99,226,164,155,164,172,165,172,167,172,119,224,224,224,224,160,151,160,172,
	0,42,95,188,188,188,188,188,188,188,188,188,103,252,67,176,252,176,236,171,236,171,236,171,236,171,236,169,236,169,236,169,236,169,236,171,236,171,236,167,236,167,75,160,172,236,67,167,236,167,236,167,236,167,236,169,236,169,236,171,236,167,236,167,236,167,236,169,236,169,236,169,236,169,236,171,236,171,236,176,252,176,252,176,252,176,236,171,236,167,236,169,236,164,236,165,236,165,236,167,236,167,236,167,236,167,75,160,172,236,67,176,252,176,252,176,252,176,252,176,252,176,252,176,236,170,236,169,236,169,236,171,236,167,236,167,236,167,236,167,236,168,236,169,236,169,236,171,236,171,252,176,252,176,252,176,252,176,252,178,252,178,252,178,252,178,236,171,236,171,236,169,236,168,236,167,236,167,236,167,236,167,236,171,236,171,75,171,172,176,188,178,188,236,67,167,236,167,236,167,75,172,236,67,167,236,167,236,167,75,172,236,67,171,236,171,75,171,172,176,188,178,188,34,132,140,132,140,135,140,138,140,144,135,128,140,1,
	0,36,87,186,186,107,250,250,250,252,186,186,250,250,250,252,127,220,220,220,220,220,220,220,220,220,220,220,115,220,99,215,217,219,160,156,156,215,220,215,215,214,212,149,156,107,220,212,213,215,153,156,71,156,99,208,148,215,160,97,218,96,224,218,153,67,151,83,152,111,224,99,216,224,216,151,75,160,215,212,213,215,119,213,151,67,151,153,155,71,160,97,219,96,224,219,153,99,215,149,97,212,96,213,212,146,99,208,119,220,220,220,220,220,220,151,97,215,96,217,215,149,97,213,96,215,213,148,97,212,96,213,212,146,97,210,96,212,210,127,208,220,
	0,0
};
const uint8_t dw3battle[]={// 891bytes
	219,1,
	0,32,65,165,164,163,162,161,160,155,154,153,152,151,150,149,148,147,146,145,144,139,138,137,136,135,134,119,197,204,197,204,213,224,219,75,156,69,151,66,152,153,218,220,218,220,213,224,219,75,156,69,151,66,152,153,218,220,218,220,66,160,160,160,160,101,224,160,160,160,160,224,236,236,160,160,160,160,224,160,160,160,160,224,236,236,75,133,208,203,204,135,202,87,138,202,66,133,134,199,196,75,133,208,203,204,135,202,87,138,202,66,133,134,199,196,149,149,149,149,213,148,148,148,148,212,147,147,147,147,211,84,156,156,66,149,149,149,149,213,148,148,148,148,212,147,147,147,147,211,84,156,156,65,133,134,135,136,137,138,139,144,145,146,147,148,149,150,151,152,153,154,155,160,161,162,163,164,
	0,32,65,153,152,151,150,149,148,147,146,145,144,40,187,186,185,184,183,182,181,180,179,178,177,176,171,170,101,233,235,233,235,233,235,233,235,233,235,233,235,233,235,233,235,32,66,137,144,137,144,137,144,137,144,137,144,137,144,137,144,137,144,135,146,139,146,135,146,139,146,135,146,139,146,135,146,139,146,97,231,213,225,209,218,215,229,209,218,199,215,197,225,199,213,197,218,215,218,199,209,213,215,218,230,209,218,198,209,218,225,198,209,218,193,198,225,198,209,218,193,198,209,214,218,225,218,198,137,144,137,144,137,144,137,144,137,144,137,144,137,144,137,144,135,146,139,146,135,146,139,146,135,146,139,146,135,146,139,146,231,213,225,209,218,215,229,209,218,199,215,197,225,199,213,197,218,215,218,199,209,213,215,218,230,209,218,198,209,218,225,198,209,218,193,198,225,198,218,209,193,198,138,145,150,154,148,148,148,148,101,212,148,148,148,148,212,220,220,148,148,148,148,212,148,148,148,148,212,220,220,40,168,176,168,176,168,176,168,176,168,176,168,176,168,176,168,176,170,177,170,177,170,177,170,177,170,177,170,177,170,177,170,177,168,176,168,176,168,176,168,176,168,176,168,176,168,176,168,176,170,177,170,177,170,177,170,177,170,177,170,177,170,177,170,177,32,136,144,144,144,208,144,144,144,144,208,144,144,144,144,208,128,128,192,128,128,192,128,128,192,128,128,136,144,144,144,208,144,144,144,144,208,144,144,144,144,208,128,128,192,128,128,192,128,128,192,128,128,40,65,169,170,171,176,177,178,179,180,181,182,183,184,185,186,187,32,144,145,146,147,148,149,150,151,152,1,
	0,32,87,140,140,40,69,166,168,166,168,166,168,166,168,166,168,166,168,166,168,166,168,165,98,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,97,229,32,209,199,197,215,209,225,197,215,193,209,40,234,213,234,32,209,193,215,197,215,40,234,245,252,234,32,215,40,229,234,32,209,40,234,246,32,214,218,40,234,32,209,214,40,234,241,252,234,32,214,198,40,234,241,230,234,32,214,218,214,40,234,165,98,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,97,229,32,209,199,197,215,209,225,197,215,193,209,40,234,213,234,32,209,193,215,197,215,40,234,245,252,234,32,215,40,229,234,32,209,40,234,246,32,214,218,40,234,32,209,214,40,234,241,252,234,32,214,198,40,234,241,98,32,198,202,209,214,40,250,250,250,250,186,250,250,250,250,186,240,230,228,225,250,250,250,250,186,250,250,250,250,186,240,230,228,225,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,165,229,229,229,248,248,248,184,248,248,248,248,184,248,248,248,248,184,224,224,160,224,224,160,224,224,160,224,224,229,248,248,248,184,248,248,248,248,184,248,248,248,248,184,224,224,160,224,224,160,224,224,160,224,224,107,227,
	0,0
};
const uint8_t allback[]={// 960bytes
	67,129,
	0,32,64,139,140,140,148,97,212,210,210,212,212,220,212,215,220,219,217,220,220,220,212,220,212,210,212,220,212,210,212,215,215,210,203,220,212,220,219,220,212,210,210,212,212,220,212,215,215,217,219,220,220,220,212,156,146,212,156,146,212,215,217,219,217,156,151,212,210,212,220,220,220,226,220,220,212,210,212,67,148,210,212,148,210,212,212,215,226,220,220,212,210,212,136,210,212,148,210,212,212,215,226,220,220,212,210,212,148,210,212,148,210,212,212,215,226,220,220,212,210,212,148,210,212,215,217,215,220,220,220,203,204,204,212,210,220,220,201,203,203,203,201,199,204,204,204,204,204,204,204,210,220,220,201,203,203,203,212,210,220,220,220,203,204,203,212,210,220,220,220,203,203,203,201,199,204,204,204,204,204,204,204,204,204,201,204,203,203,203,201,199,204,204,204,203,204,204,212,210,220,220,201,203,203,203,201,199,204,204,204,204,204,204,204,210,220,220,201,203,203,203,212,210,220,220,220,203,204,203,212,210,220,220,210,212,212,212,215,219,220,220,220,217,215,217,215,217,215,217,215,212,215,212,210,212,220,147,64,139,140,140,148,212,210,210,212,212,220,212,215,220,219,217,220,220,220,212,220,212,210,212,220,212,210,212,215,215,210,203,220,212,220,219,220,212,210,210,212,212,220,212,215,215,217,219,220,220,220,212,156,146,212,156,146,212,215,217,219,217,156,151,212,210,212,220,220,220,
	0,42,64,171,172,172,68,171,65,169,169,99,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,95,172,172,172,172,172,172,172,172,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,171,171,235,169,169,233,178,178,242,242,252,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,64,171,172,172,68,171,65,169,169,233,178,178,242,178,178,242,
	0,42,65,144,160,99,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,151,151,215,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,151,151,215,144,156,144,160,146,162,146,162,148,164,148,164,146,162,146,162,144,160,144,160,146,162,146,162,148,164,148,164,146,162,146,162,144,156,144,160,146,162,146,162,148,164,148,164,146,162,146,162,144,160,144,160,146,162,146,162,148,164,148,164,146,162,146,162,144,156,144,160,146,162,146,162,148,164,148,164,146,162,146,162,144,160,144,160,146,162,146,162,148,164,148,164,146,162,146,162,144,156,144,160,139,155,139,155,148,164,148,164,146,162,146,162,144,160,144,160,139,155,139,155,148,164,148,164,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,146,162,146,162,144,160,208,139,139,203,148,148,212,151,151,215,
	0,38,67,172,160,172,160,172,160,97,236,224,160,172,160,172,160,172,160,236,224,160,172,160,172,160,172,160,236,224,160,172,160,172,160,172,160,236,224,160,236,224,224,236,66,160,160,224,236,224,224,236,160,160,224,236,224,224,236,160,160,224,236,224,224,236,160,160,224,236,224,224,236,160,160,224,236,224,224,236,160,160,224,236,224,224,236,160,160,224,236,224,224,236,160,160,224,95,172,172,172,172,172,172,172,172,67,172,160,172,160,172,160,236,224,160,172,160,172,160,172,160,236,224,160,172,160,172,160,172,160,236,224,160,172,160,172,160,172,160,236,224,160,1,
	0,0
};
const uint8_t surfboard[]={// 1473bytes
	151,129,
	0,42,66,185,185,188,183,183,188,182,182,188,180,180,188,179,179,188,178,178,188,179,179,188,180,180,188,181,181,188,183,183,188,183,183,188,181,181,188,180,180,188,178,178,188,177,177,188,176,176,188,177,177,188,178,178,188,179,179,188,181,181,188,181,181,188,179,179,188,178,178,188,176,176,188,171,171,172,170,170,172,181,181,188,179,179,188,178,178,188,176,176,188,171,171,172,170,170,172,71,179,178,67,179,181,79,182,67,181,179,71,179,178,67,179,181,79,182,71,188,66,185,185,188,183,183,188,182,182,188,180,180,188,179,179,188,178,178,188,179,179,188,180,180,188,181,181,188,183,183,188,183,183,188,181,181,188,180,180,188,178,178,188,177,177,188,176,176,188,177,177,188,178,178,188,179,179,188,181,181,188,181,181,188,179,179,188,178,178,188,176,176,188,171,171,172,170,170,172,181,181,188,179,179,188,178,178,188,176,176,188,171,171,172,170,170,172,71,179,178,67,179,181,79,182,67,181,179,71,179,178,67,179,181,79,182,71,188,71,181,171,181,171,181,171,181,171,181,171,46,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,181,171,35,66,153,151,156,153,151,156,153,151,156,153,151,156,153,151,156,153,151,153,151,156,153,152,151,150,75,151,156,66,151,149,156,151,149,156,151,149,156,151,149,156,151,149,156,151,149,151,149,156,151,150,149,148,75,149,156,66,149,147,156,149,154,156,149,147,156,149,138,156,149,147,156,149,160,156,149,147,156,149,77,144,67,156,42,188,181,179,71,179,178,67,179,181,79,182,67,181,179,71,179,178,67,179,181,79,182,71,188,
	0,46,66,178,178,188,178,178,188,178,178,188,178,178,188,178,178,188,176,176,188,177,177,188,178,178,188,178,178,188,177,177,188,176,176,188,176,176,188,176,176,188,176,176,188,171,171,172,170,170,172,171,171,172,176,176,188,176,176,188,176,176,188,176,176,188,170,170,172,170,170,172,170,170,172,170,170,172,169,169,172,169,169,172,169,169,172,169,169,172,169,169,172,169,169,172,169,169,172,87,172,172,172,172,66,178,178,188,178,178,188,178,178,188,178,178,188,178,178,188,176,176,188,177,177,188,178,178,188,178,178,188,177,177,188,176,176,188,176,176,188,176,176,188,176,176,188,171,171,172,170,170,172,171,171,172,176,176,188,176,176,188,176,176,188,176,176,188,170,170,172,170,170,172,170,170,172,170,170,172,169,169,172,169,169,172,169,169,172,169,169,172,169,169,172,169,169,172,169,169,172,87,169,170,169,170,169,38,64,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,137,139,36,137,138,139,144,145,146,147,148,149,150,151,152,153,154,155,160,161,162,32,69,172,75,163,69,161,154,155,152,147,67,145,147,139,81,138,69,136,66,135,133,131,129,40,67,171,169,168,95,167,38,64,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,146,148,36,146,148,149,150,151,152,153,154,155,160,161,162,163,164,165,166,167,168,169,32,69,172,75,170,69,168,163,161,154,155,151,152,147,145,66,144,139,138,136,67,135,133,131,38,66,135,140,140,135,140,140,140,135,140,135,140,135,140,135,135,140,101,199,135,140,135,135,140,135,140,135,140,135,140,135,135,140,137,140,140,137,140,137,140,137,140,140,140,137,137,140,137,140,198,134,140,140,134,140,134,140,134,140,107,198,140,140,135,140,135,140,135,135,140,101,199,140,135,140,135,140,135,140,133,140,133,140,140,133,133,140,133,140,133,140,104,197,119,201,202,201,202,
	0,40,72,151,98,215,146,210,151,215,146,210,151,215,146,210,144,208,151,215,149,213,160,224,149,213,160,224,149,213,160,224,154,218,149,213,147,211,154,218,147,211,154,218,146,210,153,217,146,210,153,217,119,215,216,215,216,151,98,215,146,210,151,215,146,210,151,215,146,210,144,208,151,215,149,213,160,224,149,213,160,224,149,213,160,224,154,218,149,213,147,211,154,218,147,211,154,218,146,210,153,217,146,210,153,217,119,215,216,215,216,215,220,220,220,98,161,225,152,216,161,225,152,216,161,225,152,216,161,225,152,216,119,215,220,220,220,98,161,225,152,216,161,225,152,216,161,225,152,216,161,225,152,216,151,215,146,210,151,215,146,210,145,209,150,214,145,209,150,214,144,208,149,213,144,208,149,213,139,203,148,212,139,203,148,212,138,202,147,211,138,202,147,211,146,210,153,217,146,210,153,217,119,215,216,215,216,1,
	0,38,66,177,177,187,177,177,187,177,177,187,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,187,187,177,187,177,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,177,187,177,177,187,177,177,187,177,187,177,119,252,252,252,252,177,177,187,177,177,187,177,177,187,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,187,187,177,187,177,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,187,177,177,177,187,177,177,187,177,177,187,177,187,177,119,252,252,252,252,252,252,252,252,177,177,187,177,177,187,177,177,187,177,187,177,177,187,177,177,177,177,187,177,177,187,177,187,177,187,177,187,187,188,188,188,252,252,252,252,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,
	0,0
};

#endif