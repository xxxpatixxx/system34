import sys
import os

from discord_webhook import DiscordWebhook

Score = sys.argv[1]
user = os.environ.get('USER', os.environ.get('USERNAME'))

webhook = DiscordWebhook(url='https://discord.com/api/webhooks/1039586904330469438/08RnmHgMAzw3ubC4byeSw67Sg2x0wk41WoflZsme3DK4G8I2wgS-ssb71zQvdbrxI_Ks', content= user +" "+ Score)
response = webhook.execute()

exit(0)