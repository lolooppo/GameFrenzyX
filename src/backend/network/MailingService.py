""""
Not complete yet, to be continued later
"""


import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

class MailingService:

    @staticmethod
    def send_gmail(receiver_email: str, subject: str, message: str):
        sender_email = "your_email@gmail.com"
        app_password = "your_16_char_app_password"  # from Google App Passwords

        # Create the email
        email = MIMEMultipart()
        email["From"] = sender_email
        email["To"] = receiver_email
        email["Subject"] = subject

        # Attach message
        email.attach(MIMEText(message, "plain"))

        try:
            # Connect to Gmail SMTP server
            with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
                server.login(sender_email, app_password)
                server.send_message(email)
                print("✅ Email sent successfully!")

        except Exception as e:
            print(f"❌ Failed to send email: {e}")

