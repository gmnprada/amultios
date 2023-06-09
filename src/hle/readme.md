# Whats this ?

see the official psp firmware and the update available at

thank for the wiki on https://www.psdevwiki.com/psp/Official_Firmware_(OFW)

we try to mimic all that syscall and nids based on each firmwave major version update so we can switch version on emulating it on host machine easily from the start on each os api calls of psp sys.

Its sounds crazy even there is a possibility same function and latest firmware is better? 

deprecated or rellocation or maybe change and update of function on sdk can be seen clearly from the stub or reverse engineering the asm function. after all PSP Firmware or OS is huge so maybe leftover or deprecated API on know compiled prx had some use on olds games, if we found something common in each firmware version move that to hle_core. its how i code time to time by generating and write so many funcion at random first , and refactor later if the function had same input output or do redundant and same things. its also make easy to see if something changed in the nids or the hash of the syscall in memory.

dunno i just want a challenge to do in long run. each software SDK or firmware also had version and update so better to start from the beginning most early version of it. and seeing the changelog and compiled firmware reverse engineered data. if we mimic so many of that with HLE ways in specific psp firmware version its mean any game also created on specific firmware version or sdk version will be matched on its time to date compiled, maybe we can achieve better compability in long run instead only map the nids table to one function call.

this is a long term projects after all in a free time!.

its a milestone to virtual host and emulate the psp firmware in many different version.

# intial shipped version? according to youtube comment
To Do differentiate it with motherboard model too.
PSP-1000 (First): 1.00
PSP-1000 (Legolas): 2.00
PSP-2000: 3.60/3.9x/4.0
PSP-3000: 4.20/5.70/6.30
PSP Go/PSP-N1000: 5.70
PSP-E1000/PSP Street: 6.50/6.60

# To do add this readme to docs later and document also the firmware release date for seeing the relations on library version and encryption used